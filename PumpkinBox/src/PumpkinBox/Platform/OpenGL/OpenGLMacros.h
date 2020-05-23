#pragma once
#include "PumpkinBox/Core/Core.h"
#include "PumpkinBox/Core/Log.h"

#include <glad/glad.h>

inline static void GLClearError() { while (glGetError() != GL_NO_ERROR); }

static bool GLLogCall(const char* function, const char* file, const int line)
{
    while (GLenum error = glGetError())
    {
        PB_ERROR("[OpenGL] Error ({0}):", error);
        PB_ERROR("[OpenGL]     in function {0}", function);
        PB_ERROR("[OpenGL]     at {0} ({1})", file, line);
        return false;
    }
    return true;
}

#if defined PB_DEBUG
    #define GLCall(x) GLClearError();\
                      x;\
                      PB_ASSERT(GLLogCall(#x, __FILE__, __LINE__), "OpenGL Error!")
#else
    #define GLCall(x) x
#endif