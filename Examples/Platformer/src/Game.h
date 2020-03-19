#pragma once

#include <OpsCore.h>
#include "imgui.h"

#include "Player.h"

class Game : public oc::Layer {

public:

	Game(const std::string& name = "Layer");

	void OnAttach() override;
	void OnDetach() override;
	void OnRender() override;
	void OnUpdate(oc::Timestep ds) override;
	void OnLateUpdate(oc::Timestep ds) override;
	void OnEvent(oc::Event& event) override;
	virtual void OnImGuiRender() override;

private:

	oc::OrthographicCameraController m_CameraController;
	
	oc::GameObjectCollection m_GameObjectCollection;
	
	oc::Sprite spy_sprite;

	glm::vec2 placeholder;

	Player spy;

};