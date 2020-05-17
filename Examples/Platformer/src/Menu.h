#pragma once
#include <PumpkinBox.h>
#include "imgui.h"

class Menu : public oc::Layer {

public:

	Menu(const std::string& name = "Layer");

	void OnAttach() override;
	void OnDetach() override;
	void OnRender() override;
	void OnUpdate(oc::Timestep ds) override;
	void OnLateUpdate(oc::Timestep ds) override;
	void OnEvent(oc::Event& event) override;
	virtual void OnImGuiRender() override;

private:

	oc::OrthographicCameraController m_CameraController;
	oc::Ref<oc::Texture2D> pumpkinbox_texture;
	std::string pumpkinbox_texture_path = "assets/textures/pumpkin.png";

};