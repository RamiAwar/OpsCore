#include "pbpch.h"

#include "winInput.h"
#include "PumpkinBox/Core/Application.h"
#include <GLFW/glfw3.h>

namespace pb {

	Input* Input::s_Instance = new winInput();

	bool winInput::IsKeyPressedImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, keycode);

		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}  

	bool winInput::IsMouseButtonPressedImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, keycode);
		
		return state == GLFW_PRESS;
	}

	std::pair<float, float> winInput::GetMousePosImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return { (float)xpos, (float)ypos };
	}

	bool winInput::GetMouseXImpl()
	{
		return GetMousePosImpl().first;
	}

	bool winInput::GetMouseYImpl()
	{
		return GetMousePosImpl().second;
	}



}
