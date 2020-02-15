#pragma once

#include "OpsCore/Core.h"

namespace oc {

	class OPSCORE_API Input {
		
	public:
		inline static bool IsKeyPressed(int keycode) {
			return s_Instance->IsKeyPressedImpl(keycode);
		}

		inline static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button); }
		inline static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		inline static float GetMouseY() { return s_Instance->GetMouseYImpl(); }
		inline static std::pair<float, float> GetMousePos() { return s_Instance->GetMousePosImpl(); }
	protected:
		virtual bool IsMouseButtonPressedImpl(int keycode) = 0;
		virtual bool IsKeyPressedImpl(int keycode) = 0;
		virtual bool GetMouseXImpl() = 0;
		virtual bool GetMouseYImpl() = 0;
		virtual std::pair<float, float> GetMousePosImpl() = 0;

	private:
		static Input* s_Instance;
	};
}