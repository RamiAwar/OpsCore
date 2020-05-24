#include "pbpch.h"
#include "winWindow.h"

#include "PumpkinBox/Events/ApplicationEvent.h"
#include "PumpkinBox/Events/MouseEvent.h"
#include "PumpkinBox/Events/KeyEvent.h"

#include "PumpkinBox/Platform/OpenGL/OpenGLContext.h"
#include "PumpkinBox/Renderer/Renderer.h"

namespace pb {

	static uint8_t s_GLFWWindowCount = 0;

	static void GLFWErrorCallback(int error, const char* description) {
		PB_ERROR("GLFW Error ({0}): {1}", error, description);
	}

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

		PB_INFO("Creating window {0} ({1}, {2})", properties.Title, properties.Width, properties.Height);

		if (s_GLFWWindowCount == 0) {
			// TODO: glfwTerminate on system shutdown
			int success = glfwInit();
			PB_ASSERT(success, "Could not initialize GLFW!")
			glfwSetErrorCallback(GLFWErrorCallback);
		}

		// Set version hints before creating window
		#ifdef PB_PLATFORM_MACOS

			PB_INFO("Setting GLFW context version hints for MACOS");
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
			

		#elif defined(PB_PLATFORM_WINDOWS)
			PB_INFO("Setting GLFW context version hints for Windows");
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			glfwWindowHint(GLFW_SAMPLES, 4);
		#else
			#error "Unsupported platform";
		#endif

		m_Window = glfwCreateWindow((int)properties.Width, (int)properties.Height, m_Data.Title.c_str(), nullptr, nullptr);
		++s_GLFWWindowCount;

		// TODO: Find a more elegant solution to this
		Renderer::screenWidth = (int)properties.Width;
		Renderer::screenHeight = (int)properties.Height;
		Renderer::aspectRatio = (float)properties.Width / properties.Height;

		m_Context = new OpenGLContext(m_Window);
		m_Context->Init();

		

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		// Set GLFW callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) 
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;

			WindowResizeEvent event(width, height);
			data.EventCallback(event);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			WindowCloseEvent event;
			data.EventCallback(event);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action) {
			case GLFW_PRESS:
			{
				KeyPressedEvent event(key, 0);
				data.EventCallback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				KeyReleasedEvent event(key);
				data.EventCallback(event);
				break;
			}
			case GLFW_REPEAT:
			{
				KeyPressedEvent event(key, 1);
				data.EventCallback(event);
				break;
			}}
		});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			KeyTypedEvent event(keycode);
			data.EventCallback(event);
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action) {
			case GLFW_PRESS:
			{
				MouseButtonPressedEvent event(button);
				data.EventCallback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				MouseButtonReleasedEvent event(button);
				data.EventCallback(event);
				break;
			}}
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float) xOffset, (float) yOffset);
			data.EventCallback(event);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseMovedEvent event((float)xPos, (float)yPos);
			data.EventCallback(event);
		});
	}

	void winWindow::Shutdown() {
		glfwDestroyWindow(m_Window);
		if (--s_GLFWWindowCount == 0)
		{
			PB_INFO("Terminating GLFW");
			glfwTerminate();
		}
	}

	void winWindow::OnUpdate() {
		glfwPollEvents();
		m_Context->SwapBuffers();
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
	