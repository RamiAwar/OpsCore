/* -*- coding: utf-8 -*-
 * This file is part of Pathie.
 *
 * Copyright © 2015, 2017, 2019 Marvin Gülker
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * “AS IS” AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */




#pragma once





/*

Used API
------------------
Path path("assets/textures/shader.glsl");
path.basename().str(); // shader.glsl
path.dirname().str(); // assets/textures
path.extension(); // .glsl

*/




#include "ocpch.h"

#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <cstring>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdexcept>
#include <errno.h>

#if defined(_WIN32)
#include <windows.h>
#include <winioctl.h>
#include <direct.h>
#include <shlobj.h>
#include <shlwapi.h>
 //#include <ntifs.h> // Currently not in msys2
#ifndef F_OK
#define F_OK 0
#endif
#ifndef W_OK
#define W_OK 2
#endif
#ifndef R_OK
#define R_OK 4
#endif

#elif defined(_PATHIE_UNIX)
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/param.h> // defines "BSD" macro on BSD systems
#include <pwd.h>
#include <glob.h>
#include <fnmatch.h>

#else
#error Unsupported system.
#endif

#ifdef BSD
#include <sys/time.h>
#include <sys/sysctl.h>
#endif

#ifdef __APPLE__
#include <mach-o/dyld.h>
#endif

class Path {

public:
    /**
     * The default constructor. It does **not** create an empty
     * path, but a path whose value is ".", i.e. the current
     * working directory as a relative path (see also pwd()).
     */
    Path()
    {
        m_path = ".";
    }

    /**
     * Copies contents from path to a new instance.
     *
     * \param[in] path The Path instance to copy.
     */
    Path(const Path& path)
    {
        m_path = path.m_path;
    }

    /**
     * This constructs a path from a given std::string. The path is
     * automatically sanitized, i.e. backslashes are replaced with forward
     * slashes (Windows perfectly well handles path separation with
     * forward slashes), double slashes are replaced with a single slash,
     * and a trailing slash (if exists) is removed.
     *
     * \param path String to construct from. Must be encoded in UTF-8.
     *
     * \returns a new instance of class Path.
     *
     * \remark On Windows, UNC paths (paths starting with a double leading
     * forward or backward slash) are allowed. The constructor is not
     * going to strip the double slash away. On UNIX, leading double
     * slashes (forward and backward) are sanitised into a single leading
     * (forward) slash.
     */
    Path(std::string path)
    {
        m_path = path;
        sanitize();
    }

    /**
     * Constructs a Path instance from a list of path components.
     * This is the inverse of the burst() method.
     *
     * \param[in] components List of components to join.
     *
     * \returns A new instance.
     */
    Path(const std::vector<Path>& components)
    {
        m_path = components.front().m_path;

        if (components.size() > 1) {
            // Ensure that for both absolute and relative path we end in
            // a slash for appending below
            if (m_path[0] != '/') {
                m_path += "/";
            }

            std::vector<Path>::const_iterator iter;
            for (iter = components.begin() + 1; iter != components.end(); iter++) { // first element has already been taken care of above
                m_path += (*iter).m_path + "/";
            }

            // Trailing slash is unwanted, remove it
            m_path = m_path.substr(0, m_path.length() - 1);
        }
    }

    /**
     * Sanitizes the path. It:
     *
     * 1. Replaces any backslashes with forward slashes (read Windows).
     * 2. Replaces all double forward slashes with single forward slashes
     * 3. Delates a trailing slash, if any.
     */
    void sanitize()
    {
        #ifdef _WIN32
        bool is_unc = m_path.length() > 2 && (m_path.substr(0, 2) == "\\\\" || m_path.substr(0, 2) == "//");
        #else
        bool is_unc = false;
        #endif

        // Replace any backslashes \ with forward slashes /.
        size_t cur = std::string::npos;
        while ((cur = m_path.find("\\")) != std::string::npos) { // assignment intended
            m_path.replace(cur, 1, "/");
        }

        // Replace all double slashes // with a single one,
        // except for UNC pathes on Windows.
        cur = std::string::npos;
        while ((cur = m_path.find("//", is_unc ? 1 : 0)) != std::string::npos) { // assignment intended
            m_path.replace(cur, 2, "/");
        }

        // Remove trailing slash if any (except for the filesystem root)
        long len = m_path.length();
        #if defined(_PATHIE_UNIX)
        if (len > 1 && m_path[len - 1] == '/')
            m_path = m_path.substr(0, len - 1);
        #elif defined(_WIN32)
        if (len > 1) { // / is root of current drive, "x" is the relative path "./x"
          // Check if X:/foo/bar
            if (len > 3 && m_path[len - 1] == '/') { // More than 3 chars cannot be root
                m_path = m_path.substr(0, len - 1);
            }
            else { // Only drive root?
                if (m_path[1] == ':') {
                    // Here m_path must be a drive root. The colon ":" is not allowed in paths on Windows except as the 2nd char to denote the drive letter
                    if (len == 2) { // Whoa -- "X:" misses leading / for drive root, append it
                        m_path.append("/");
                    }
                    else if (len == 3 && m_path[2] != '/') { // Whoa -- "X:f" misses leading / for root directory, insert it
                        m_path.insert(2, "/");
                    }
                    // else length is 3 with a slash, i.e. "X:/". This is fine and shall not be touched.
                }
                else { // not a drive root, delete trailing / if any
                    if (m_path[len - 1] == '/') {
                        m_path = m_path.substr(0, len - 1);
                    }
                }
            }
        }
        #else
        #error Unsupported system
        #endif
    }

    /** \name Conversion methods
     *
     * Convert a path to other objects.
     */
     ///@{

     /**
      * Returns a copy of the underlying `std::string`. This is always
      * encoded in UTF-8, regardless of the operating system.
      *
      * \see native() utf8_str()
      */
    std::string str() const
    {
        return m_path;
    }


    /** \name Path decomposition
     *
     * Retrieve the parts of the path you want.
     */
     ///@{

     /**
      * Returns the path’s basename, i.e. the last component
      * of the path, including the file excention.
      *
      * For example, "/foo/bar.txt" has a basename of "bar.txt",
      * and "/foo/bar" has a basename of "bar".
      *
      * \returns a new Path instance with only the basename.
      *
      * \see dirname()
      */
    Path basename() const
    {
        if (m_path == ".")
            return Path(".");
        else if (m_path == "..")
            return Path("..");
        else if (is_root())
            return Path(m_path);

        size_t pos = 0;
        if ((pos = m_path.rfind("/")) != std::string::npos) // Single = intended
            return Path(m_path.substr(pos + 1));
        else
            return Path(m_path);
    }

    /**
     * Returns the path’s dirname, i.e. all components of the
     * path except for the basename component (see basename()).
     *
     * For example, "/foo/bar/baz.txt" has a dirname of "/foo/bar",
     * and "/foo/bar/baz" has a dirname of "/foo/bar".
     *
     * \returns a new Path instance with only the dirname.
     *
     * \see basename() parent()
     */
    Path dirname() const
    {
        if (m_path == ".")
            return Path(".");
        else if (m_path == "..")
            return Path(".");
        else if (is_root())
            return Path(m_path);

        size_t pos = 0;
        if ((pos = m_path.rfind("/")) != std::string::npos) { // Single = intended
            if (pos == 0) { // /usr
                return root();
            }
            #ifdef _WIN32
            else if (pos == 1 && m_path[1] == ':') { // X:/foo
                return root();
            }
            #endif
            else { // regular/path or /regular/path
                return Path(m_path.substr(0, pos));
            }
        }
        else // single relative directory
            return Path(".");
    }

    /**
     * This is a convenience method that allows you to retrieve
     * both the dirname() and the basename() in one call.
     *
     * \param[out] dname Receives the dirname() value.
     * \param[out] bname Receives the basename() value.
     */
    void split(Path& dname, Path& bname) const
    {
        dname = dirname();
        bname = basename();
    }

    /**
     * This method returns the file extension of the path,
     * if possible; otherwise it returns an empty string.
     * Filenames that consist entirely of a "file extension",
     * i.e. ".txt" or "/foo/.txt" will return an empty string.
     */
    std::string extension() const
    {
        if (m_path == ".")
            return "";
        else if (m_path == "..")
            return "";

        size_t pos = 0;
        if ((pos = m_path.rfind(".")) != std::string::npos) { // assignment intended
            if (pos == 0 || pos == m_path.length() - 1) // .foo and foo.
                return "";
            else {
                if (m_path[pos - 1] == '/') // foo/.txt
                    return "";
                else
                    return m_path.substr(pos);
            }
        }
        else
            return "";
    }

    /**
 * Checks if this path is a filesystem root. On UNIX, this
 * is the case if the path consists solely of one slash, on
 * Windows this is the case if the path looks like this:
 * "<letter>:/".
 */
    bool is_root() const
    {
        #if defined(_PATHIE_UNIX)
        return m_path.length() == 1 && m_path[0] == '/';
        #elif defined(_WIN32)
        // / on Windows is root on current drive
        if (m_path.length() == 1 && m_path[0] == '/')
            return true;

        // X:/ is root including drive letter
        return m_path.length() == 3 && m_path[1] == ':';
        #else
        #error Unsupported platform.
        #endif
    }

    /**
 * Returns the filesystem root for this path. On UNIX,
 * this will always return /, but on Windows it will
 * return X:/ if the referenced path is an absolute path
 * with drive letter, and / if the referenced path is
 * a relative path or an absolute path on the current
 * drive.
 */
    Path root() const
    {
        #if defined(_PATHIE_UNIX)
        return Path("/");
        #elif defined(_WIN32)
        // Check if we have an absolute path with drive,
        // otherwise return the root for the current drive.
        if (m_path[1] == ':') // Colon is on Windows only allowed here to denote a preceeding drive letter => absolute path
            return Path(m_path.substr(0, 3));
        else
            return Path("/");
        #else
        #error Unsupported system.
        #endif
    }

    Path basename_strip_extension() {
        Path path = Path(m_path);
        std::string basepath = path.basename().str();
        size_t pos = basepath.find(path.extension());
        return Path(basepath.substr(0, pos));
    }


    private:
        std::string m_path;

};