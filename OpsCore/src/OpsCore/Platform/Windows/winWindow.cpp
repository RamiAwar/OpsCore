#include "ocpch.h"
#include "winWindow.h"

namespace oc {

	static bool s_GLFWInitialized = false;

	Window* Window::Create(const WindowProperties& properties) {
		return new winWindow(properties);
	}

	Window::~Window() {}

	winWindow::winWindow(const WindowProperties& properties) {
		Init(properties);
	}

	winWindow::~winWindow() { 
		Shutdown();
	}

	void winWindow::Init(const WindowProperties& properties) {
		m_Data.Title = properties.Title;
		m_Data.Width = properties.Width;
		m_Data.Height = properties.Height;

		OC_INFO("Creating window {0} ({1}, {2})", properties.Title, properties.Width, properties.Height);

		if (!s_GLFWInitialized) {

			// TODO: glfwTerminate on system shutdown
			int success = glfwInit();
			OC_ASSERT(success, "Could not initialize GLFW!")
			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)properties.Width, (int)properties.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);
	}

	void winWindow::Shutdown() {
		glfwDestroyWindow(m_Window);
	}

	void winWindow::OnUpdate() {
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void winWindow::SetVSync(bool enabled) {
		if (enabled) glfwSwapInterval(1);
		else glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool winWindow::IsVSync() const {
		return m_Data.VSync;
	}
}
	