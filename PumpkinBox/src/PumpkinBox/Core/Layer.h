#pragma once

#include "PumpkinBox/Core/Core.h"
#include "PumpkinBox/Events/Event.h"
#include "PumpkinBox/Core/Timestep.h"


// Forward declaration of Scene class

namespace pb {
	
	class  Layer
	{
	public:

		Layer(const std::string& name="Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		
		// OnUpdate() 
		// For updating object transforms, animation states, etc.
		// Called once every loop
		virtual void OnUpdate(Timestep ds) {}
		
		// OnLateUpdate()
		// After update, for collision detection and things that 
		// depend on update function's changes
		virtual void OnLateUpdate(pb::Timestep ds) {}
		virtual void OnRender() {}
		virtual void OnEvent(Event& event) {}
		virtual void OnImGuiRender() {}

		inline const std::string& GetName() const { return m_DebugName; }

	protected:
		std::string m_DebugName;

	};

}
