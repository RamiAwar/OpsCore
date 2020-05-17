#include "pbpch.h"
#include "SceneStateMachine.h"


namespace pb {

	SceneStateMachine* SceneStateMachine::s_Instance = 0;

	void SceneStateMachine::OnEvent(Event& e) {
		m_CurrentScene->OnEvent(e);
	}

	void SceneStateMachine::OnUpdate(pb::Timestep ts, bool minimized) {
		
		m_CurrentScene->OnUpdate(ts, minimized);

		if (m_CurrentScene->GetShutdown()) {
			
			m_CurrentScene->ToggleShutdown();
			m_CurrentScene->OnDetach();

			m_CurrentScene = m_QueuedScene;
			m_CurrentSceneName = m_QueuedSceneName;

			m_CurrentScene->OnInit();
			m_CurrentScene->OnAttach();
		}
	}

	void SceneStateMachine::Add(std::string name, Ref<Scene> scene) {
		
		PB_ASSERT(!Find(name), "Scene named :'{}' already exists in this scene state machine.", name);
		m_SceneList[name] = scene;

		if (m_CurrentScene == NULL) {
			SetActive(name);
		}
	}

	void SceneStateMachine::SetActive(std::string name) {

		PB_ASSERT(Find(name), "Scene named :'{}' was not found.", name);
		 
		if (m_CurrentScene != NULL) {
			m_CurrentScene->ToggleShutdown();

			m_QueuedScene = m_SceneList[name];
			m_QueuedSceneName = name;
		}
		else {
			m_CurrentScene = m_SceneList[name];
			m_CurrentSceneName = name;
			m_CurrentScene->OnInit();
			m_CurrentScene->OnAttach();
		}

		

	}

	//Ref<Scene> SceneStateMachine::GetActive() {
	//	return m_CurrentScene;
	//}

	void SceneStateMachine::Remove(std::string name) {
		PB_ASSERT(m_CurrentSceneName != name, "Cannot remove currently active scene. Please change scenes first before removing.");
		m_SceneList.erase(name);
	}

	bool SceneStateMachine::Find(std::string name) {
		return m_SceneList.find(name) != m_SceneList.end();
	}

}