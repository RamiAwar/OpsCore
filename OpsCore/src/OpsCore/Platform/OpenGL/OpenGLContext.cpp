#include "ocpch.h"
#include "OpenGLContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.hy>

oc::OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
	: m_WindowHandle(windowHandle)
{
	OC_ASSERT(windowHandle, "Window handle in OpenGLContext constructor is null.");
}

void oc::OpenGLContext::Init()
{
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
