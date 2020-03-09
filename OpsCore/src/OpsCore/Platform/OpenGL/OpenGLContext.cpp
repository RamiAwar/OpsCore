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
	glfwMakeContextCurrent(m_WindowHandle);


#ifdef OC_PLATFORM_MACOS

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	
#elif defined(OC_PLATFORM_WINDOWS)

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#endif

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
