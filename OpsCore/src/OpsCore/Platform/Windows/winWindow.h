#pragma once

#include "OpsCore/Window.h"

#include <GLFW/glfw3.h>

namespace oc {

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

		inline virtual void* GetNativeWindow() const { return m_Window; }

	private:
		virtual void Init(const WindowProperties& properties);
		virtual void Shutdown();

		GLFWwindow* m_Window;

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