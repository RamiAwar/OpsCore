#pragma once

#include "OpsCore/Core/Core.h"

#include "OpsCore/Core/Timestep.h"
#include "OpsCore/Core/Scene.h"

namespace oc{

	class SceneStateMachine
	{
	public:

		SceneStateMachine(SceneStateMachine const&) = delete;
		void operator=(SceneStateMachine const&) = delete;

		static SceneStateMachine* instance() {
			if (s_Instance == NULL) s_Instance = new SceneStateMachine();
			return s_Instance;
		}

		void OnEvent(Event& e);
		// TODO: Get rid of minimized boolean here by making application window accessible?
		void OnUpdate(Timestep ts, bool minimized);

		void SetActive(std::string name);

		void Add(std::string name, Ref<Scene> scene);
		void Remove(std::string name);

		bool Find(std::string name);

	private:

		static SceneStateMachine* s_Instance;

		SceneStateMachine() {} // Private constructor

		std::unordered_map<std::string, Ref<Scene>> m_SceneList;
		Ref<Scene> m_CurrentScene, m_QueuedScene;
		std::string m_CurrentSceneName, m_QueuedSceneName;
	};

}
