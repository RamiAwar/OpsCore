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
	
	// TODO: Don't want to store textures here. Only sprites
	oc::Ref<oc::Texture2D> spy_texture;
	std::string spy_texture_path = "assets/sprites/spy/spy.atlas.png";
	glm::vec2 placeholder = glm::vec2(0.0f);
	int sprite_index = 0;

	Player spy;

};