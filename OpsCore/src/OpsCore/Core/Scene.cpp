#include "ocpch.h"
#include "Scene.h"

#include "OpsCore/Core/Input.h"
#include "OpsCore/Core/Application.h"

#include "OpsCore/Renderer/Renderer.h"
#include "OpsCore/Renderer/RenderCommand.h"

#include <GLFW/glfw3.h>

namespace oc {

	ImGuiLayer* Scene::m_ImGuiLayer = new ImGuiLayer();

	void Scene::OnInit() {

	}

	void Scene::OnAttach() {
	}

	void Scene::OnDetach() {
		m_LayerStack->Clear();
	}


	void Scene::OnEvent(Event& e) {

		for (auto it = m_LayerStack->end(); it != m_LayerStack->begin();) {
			(*(--it))->OnEvent(e);
			if (e.m_Handled) break;	// so if overlay handles event, layers will not receive it (ex. clicking button on UI, we don't want click to be propagated into game layer)
		}
	}

	void Scene::OnUpdate(oc::Timestep deltaTime, bool minimized) {

		// Iterate over layers and run update
		if (!minimized) {
			for (Layer* layer : *m_LayerStack) {
				layer->OnUpdate(deltaTime);
			}
			for (Layer* layer : *m_LayerStack) {
				layer->OnRender();
			}
		}

		m_ImGuiLayer->Begin();
		for (Layer* layer : *m_LayerStack) {
			layer->OnImGuiRender();
		}
		m_ImGuiLayer->End();

	}

	void Scene::ToggleShutdown() {
		m_Shutdown = !m_Shutdown;
	}

	void Scene::PushLayer(Layer* layer) {
		m_LayerStack->PushLayer(layer);
	}

	void Scene::PushOverlay(Layer* layer) {
		m_LayerStack->PushOverlay(layer);
	}

}