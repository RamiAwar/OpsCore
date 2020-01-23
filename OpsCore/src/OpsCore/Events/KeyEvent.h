#pragma once

#include "Event.h"

#include <sstream>

namespace oc {

	class OPSCORE_API KeyEvent : public Event {
	public:

		inline int GetKeyCode() const { return m_KeyCode; }
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

	protected:
		KeyEvent(int keycode) : m_KeyCode(keycode) {}

		int m_KeyCode;
	};

	class OPSCORE_API KeyPressedEvent : public KeyEvent {
	public:
		// Why include key repetitions? Because we don't want several events captured with one key press
		// For example pressing through menu buttons - holding a key shouldnt loop quickly between options
		// Also pressing key very quickly could send several events which is not expected behavior
		KeyPressedEvent(int keycode, int repeatCount) :KeyEvent(keycode), m_RepeatCount(repeatCount) {}

		inline int GetRepeatCount() const { return m_RepeatCount; }


		// TODO: Possibly replace this with macro?
		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repetitions)";
			return ss.str();
		}
		
		EVENT_CLASS_TYPE(KeyPressed)
	
	private:
		int m_RepeatCount;
	};

	class OPSCORE_API KeyReleasedEvent : public KeyEvent {
	public: 
		KeyReleasedEvent(int keycode) : KeyEvent(keycode) {}
		
		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repetitions)";
			return ss.str();
		}
	};

}