#pragma once

#include "OpsCore/Events/Event.h"
#include "OpsCore/Core/Timestep.h"

namespace oc {

	class GameObject; // Forward declaration 

	class Component {

	public:

		Component(GameObject* parent) :m_ParentGameObject(parent) {}

		virtual void OnCreate() = 0;
		virtual void OnDestroy() = 0;
		virtual void OnEvent(Event& e) = 0;
		virtual void OnUpdate(Timestep ts) = 0;
		virtual void OnLateUpdate(Timestep ts) = 0;
		virtual void Render() = 0;

	public:
		GameObject* m_ParentGameObject;

	protected:
		

	};

}