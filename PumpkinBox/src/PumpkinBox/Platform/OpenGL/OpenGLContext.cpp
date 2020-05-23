#include "pbpch.h"
#include "OpenGLContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

pb::OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
	: m_WindowHandle(windowHandle)
{
	PB_ASSERT(windowHandle, "Window handle in OpenGLContext constructor is null.");
}

void pb::OpenGLContext::Init()
{
	glfwMakeContextCurrent(m_WindowHandle);

	int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	PB_ASSERT(status, "Failed to initialize GLAD.");
	PB_INFO("OpenGL Renderer:");
	PB_INFO("     Vendor: {0}", glGetString(GL_VENDOR));
	PB_INFO("     Renderer: {0}", glGetString(GL_RENDERER));
	PB_INFO("     Version: {0}", glGetString(GL_VERSION));
}

void pb::OpenGLContext::SwapBuffers()
{
	glfwSwapBuffers(m_WindowHandle);
}
