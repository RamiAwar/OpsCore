#pragma once
#include "OpsCore/Core/Core.h"
#include "OpsCore/Core/Log.h"

#include <glad/glad.h>

inline static void GLClearError() { while (glGetError() != GL_NO_ERROR); }

static bool GLLogCall(const char* function, const char* file, const int line)
{
    while (GLenum error = glGetError())
    {
        OC_ERROR("[OpenGL] Error ({0}):", error);
        OC_ERROR("[OpenGL]     in function {0}", function);
        OC_ERROR("[OpenGL]     at {0} ({1})", file, line);
        return false;
    }
    return true;
}

#if defined OC_DEBUG
    #define GLCall(x) GLClearError();\
                      x;\
                      OC_ASSERT(GLLogCall(#x, __FILE__, __LINE__), "OpenGL Error!")
#else
    #define GLCall(x) x
#endif