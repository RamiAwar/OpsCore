#include "ocpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

oc::OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
	: m_WindowHandle(windowHandle)
{
	OC_ASSERT(windowHandle, "Window handle in OpenGLContext constructor is null.");
}

void oc::OpenGLContext::Init()
{


#ifdef OC_PLATFORM_MACOS

	OC_TRACE("here");
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	OC_TRACE("set");

#elif defined(OC_PLATFORM_WINDOWS)

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#else
	#error "Undefined platform!"
#endif

	glfwMakeContextCurrent(m_WindowHandle);

	int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	OC_ASSERT(status, "Failed to initialize GLAD.");
	OC_INFO("OpenGL Renderer:");
	OC_INFO("     Vendor: {0}", glGetString(GL_VENDOR));
	OC_INFO("     Renderer: {0}", glGetString(GL_RENDERER));
	OC_INFO("     Version: {0}", glGetString(GL_VERSION));
}

void oc::OpenGLContext::SwapBuffers()
{
	glfwSwapBuffers(m_WindowHandle);
}
