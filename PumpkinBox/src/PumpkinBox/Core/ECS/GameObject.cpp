#include "pbpch.h"
#include "GameObject.h"

namespace oc {


	GameObject::GameObject() {}

	void GameObject::OnCreate() {
		for (auto element : m_ComponentList) {
			element.second->OnCreate();
		}
	}

	void GameObject::OnDestroy() {
		for (auto element : m_ComponentList) {
			element.second->OnDestroy();
		}
	}
	void GameObject::OnUpdate(Timestep ts) {
		for (auto element : m_ComponentList) {
			element.second->OnUpdate(ts);
		}
	}
	void GameObject::OnLateUpdate(Timestep ts) {
		for (auto element : m_ComponentList) {
			element.second->OnLateUpdate(ts);
		}
	}
	void GameObject::Render(){
		for (auto element : m_ComponentList) {
			element.second->Render();
		}
	}


	bool GameObject::Find(const std::string& name) {
		return m_ComponentList.find(name) != m_ComponentList.end();
	}

	void GameObject::AddComponent(const std::string& name, const Ref<Component>& component) {
		OC_ASSERT(!Find(name), "Cannot add component {}: Component already exists!", name);
		m_ComponentList[name] = component;
		PB_INFO("Added component {}", name);
	}

	void GameObject::RemoveComponent(const std::string& name) {
		OC_ASSERT(Find(name), "Cannot remove component {}: It does not exist.", name);
		m_ComponentList.erase(name);
	}

	Ref<Component> GameObject::GetComponent(const std::string& name) {
		OC_ASSERT(Find(name), "GetComponent: Cannot find component {}: It does not exist.", name);
		return m_ComponentList[name];
	}


}