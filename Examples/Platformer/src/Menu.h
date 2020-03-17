#pragma once
#include <OpsCore.h>
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

};