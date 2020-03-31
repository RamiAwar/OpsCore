#pragma once
#include "OpsCore/Core/GameObject.h"

namespace oc {


	class GameObjectCollection
	{

	public:
		GameObjectCollection(){}
	
		void AddGameObject(Ref<GameObject> gameObject);

		// TODO: Add remove game object functionality to be added in visual engine editor but not in game

		void OnCreate();
		void OnDestroy();
		void OnUpdate(Timestep ts);
		void OnLateUpdate(Timestep ts);
		void Render();

	private:
		
		std::vector<Ref<GameObject>> m_GameObjectList;
		std::vector<Ref<GameObject>> m_NewGameObjectList;

	};




}