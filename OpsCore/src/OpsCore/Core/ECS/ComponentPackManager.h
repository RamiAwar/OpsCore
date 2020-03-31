#pragma once

#include "OpsCore/Core/Core.h"
#include "OpsCore/Core/Log.h"
#include <unordered_set>

#include "ComponentPack.h"

// TODO: Refactor repeated code segment into a private function

namespace oc {


	class ComponentPackManager {
		
	public:

		template<typename T>
		void RegisterComponent() {

			const char* type = typeid(T).name();
			OC_ASSERT(m_ComponentTypes.find(type) == m_ComponentTypes.end(), "Attempting to register component of type {} more than once!", type);

			m_ComponentTypes.insert(type);
			m_ComponentPackList.insert({type, CreateRef<ComponentPack<T>>()});
		}

		template<typename T>
		T& GetComponent(Entity entity) {
			const char* type = typeid(T).name();
			OC_ASSERT(m_ComponentTypes.find(type) != m_ComponentTypes.end(), "Component of type {} has not been registered!", type);

			return std::static_pointer_cast<ComponentPack<T>>(m_ComponentPackList[type])->GetComponent(entity);
		}

		template<typename T>
		void BindComponent(Entity entity) {
			const char* type = typeid(T).name();
			OC_ASSERT(m_ComponentTypes.find(type) != m_ComponentTypes.end(), "Component of type {} has not been registered!", type);

			std::static_pointer_cast<ComponentPack<T>>(m_ComponentPackList[type])->Create(entity);
		}

		template<typename T>
		void UnbindComponent(Entity entity) {
			const char* type = typeid(T).name();
			OC_ASSERT(m_ComponentTypes.find(type) != m_ComponentTypes.end(), "Component of type {} has not been registered!", type);

			std::static_pointer_cast<ComponentPack<T>>(m_ComponentPackList[type])->Remove(entity);
		}


	private:
		std::unordered_set<const char *> m_ComponentTypes;
		std::unordered_map<const char*, Ref<IComponentPack>> m_ComponentPackList;
	
	};

}