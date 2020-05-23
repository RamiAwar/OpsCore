#pragma once

#include "PumpkinBox/Core/Window.h"
#include "PumpkinBox/Renderer/GraphicsContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#ifdef PB_PLATFORM_WINDOWS
	#include <Windows.h>
#endif

namespace pb {

	


	class winWindow : public Window {
	public:
		winWindow(const WindowProperties& props);
		virtual  ~winWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		// Window attributes
		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		inline virtual void* GetNativeWindow() const override { return m_Window; }

		#ifdef PB_PLATFORM_WINDOWS

		static void HideConsole()
		{
			::ShowWindow(::GetConsoleWindow(), SW_HIDE);
		}

		static void ShowConsole()
		{
			::ShowWindow(::GetConsoleWindow(), SW_SHOW);
		}

		static bool IsConsoleVisible()
		{
			return ::IsWindowVisible(::GetConsoleWindow()) != FALSE;
		}

		#endif

	private:
		virtual void Init(const WindowProperties& properties);
		virtual void Shutdown();

		GLFWwindow* m_Window;
		GraphicsContext* m_Context;

		// Data that might be requested by GLFW by event callbacks
		struct WindowData {

			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;


	};

}