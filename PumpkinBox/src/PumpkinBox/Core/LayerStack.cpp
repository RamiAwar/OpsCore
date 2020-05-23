#include "pbpch.h"
#include "LayerStack.h"


// Simple explanation of LayerStack: 
// Vectors used to store layers and overlays, which are simply layers
// Overlays are always after layers (pushed to the back of the list)
// Layers are always pushed before the first overlay

namespace pb {

	LayerStack::LayerStack() {}

	LayerStack::~LayerStack() {}

	void LayerStack::Clear() {

		for (auto it = m_Layers.begin(); it != m_Layers.end(); it++) {
			PB_INFO("Deleting layer {}", (*it)->GetName());
			(*it)->OnDetach();
			delete *it;
		}

		m_LayerInsertIndex = 0;
		m_Layers.clear();
	}

	void LayerStack::PushLayer(Layer* layer) {
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
		m_LayerInsertIndex++;
		layer->OnAttach();
	}


	void LayerStack::PushOverlay(Layer* overlay) {
		m_Layers.emplace_back(overlay);
		overlay->OnAttach();
	}


	// Note that this won't delete layer really
	void LayerStack::PopLayer(Layer* layer) {
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end()) {
			layer->OnDetach();
			m_Layers.erase(it);
			m_LayerInsertIndex--;
		}
	}

	void LayerStack::PopOverlay(Layer* overlay) {
		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
		if (it != m_Layers.end()) {
			overlay->OnDetach();
			m_Layers.erase(it);
		}
	}

}