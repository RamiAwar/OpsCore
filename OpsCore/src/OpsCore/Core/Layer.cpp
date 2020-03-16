#include "ocpch.h"
#include "Layer.h"

namespace oc {

	Layer::Layer(Scene* scene, const std::string& debugName) :
		m_DebugName(debugName),
		m_ParentScene(scene)
	{
	}

	Layer::~Layer() {}


}
