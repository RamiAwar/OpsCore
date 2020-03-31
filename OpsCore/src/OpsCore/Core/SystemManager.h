#pragma once

#include "System.h"

#include <unordered_map>

namespace oc {

	class SystemManager {
	public:

		template<typename T>
		Ref<T> RegisterSystem() {
			
			const char* type = typeid(T).name();
			OC_ASSERT(m_SystemList.find(type) == m_SystemList.end(), "Attempting to register system of type {} more than once!", type);

			auto system = CreateRef<T>();
			m_SystemList.insert({ type, system });
			return system;
		}

	private:
		std::unordered_map<const char*, Ref<System>> m_SystemList;

	};

}