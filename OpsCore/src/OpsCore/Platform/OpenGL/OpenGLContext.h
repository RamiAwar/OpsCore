#pragma once
#include "OpsCore/Renderer/GraphicsContext.h"

struct GLFWwindow; // forward declaration so we don't have to include it here

namespace oc {

	class OpenGLContext : public GraphicsContext {

	public: 
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:
		GLFWwindow* m_WindowHandle;

	};


}