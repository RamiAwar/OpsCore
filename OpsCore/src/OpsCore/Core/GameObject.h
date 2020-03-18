#pragma once
#include "Component.h"
#include "Transform.h"

namespace oc {

	class GameObject
	{
	public:

		GameObject();

		Transform transform;

		virtual void OnCreate();
		virtual void OnDestroy();
		virtual void OnUpdate(Timestep ts);
		virtual void OnLateUpdate(Timestep ts);
		virtual void Render();

		Transform* GetTransform() { return &transform; }

		void AddComponent(const std::string& name, const Ref<Component>& component);
		Ref<Component> GetComponent(const std::string& name);
		void RemoveComponent(const std::string& name);
		bool Find(const std::string& name);



	private:
		std::string tag;
		std::unordered_map<std::string , Ref<Component>> m_ComponentList;
	
	};

}