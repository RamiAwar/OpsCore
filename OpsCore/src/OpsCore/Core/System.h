#pragma once

#include <unordered_set>

#include "Entity.h"
#include "ComponentPack.h"
#include "ComponentPackManager.h"
#include "OpsCore/Core/Timestep.h"

namespace oc {

	class System {

	public:
		virtual void Init() = 0;
		virtual void Update(Timestep ts) = 0;

	private:
		std::unordered_set<Entity> m_Entities;
	};

}