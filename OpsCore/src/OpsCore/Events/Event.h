#pragma once

#include "OpsCore/Core.h"

#include <string>
#include <functional>

namespace oc {

	// Events are currently blocking
	// TODO: Event buffer, events picked up once per main loop iteration

	enum class EventType {
		None = 0,
		WindowClose,
		WindowResize,
		WindowFocus,
		WindowLostFocus,
		WindowMoved,
		AppTick,
		AppUpdate,
		AppRender,
		KeyPressed,
		KeyReleased,
		MouseButtonPressed,
		MouseButtonReleased,
		MouseMoved,
		MouseScrolled
	};

	enum EventCategory {
		None = 0,
		EventCategoryApplication = BIT(0), // defined in 'Core.h'
		EventCategoryInput = BIT(1),
		EventCategoryKeyboard = BIT(2),
		EventCategoryMouse = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};

	// To be able to check at runtime which event type this is, 
	#define EVENT_CLASS_TYPE(type) static EventType GetStaticType(){return EventType::type;}\
						virtual EventType GetEventType() const override {return GetStaticType();} \
						virtual const char* GetName() const override {return #type; } // preprocessor # operator encloses replaced parameter with quotations

	#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override {return category;}

	class OPSCORE_API Event {
	public:
		bool Handled = false;

		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category) {
			return GetCategoryFlags() & category;
		}

	};

	class OPSCORE_API EventDispatcher {

		// why "using" instead of typedef? typedef doesn't allow templated aliases. simple.
		template <typename T>
		using EventFn = std::function<bool(T&)>; // a function that takes a template reference input, returns a bool
		
	public:
		// Events received as event reference, no idea what it actually is.
		// So create instance of a class with type received.
		EventDispatcher(Event& event) :m_Event(event) {}
		 
		template<typename T>
		bool Dispatch(EventFn<T> func) {
			if (m_Event.GetEventType() == T::GetStaticType()){
				m_Event.m_Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e) {
		return os << e.ToString();
	}

}