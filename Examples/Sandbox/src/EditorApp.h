#include <PumpkinBox.h>
#include "imgui.h"

#include "PumpkinBox/Core/Entrypoint.h"

#include "GameLayer.h"

class EditorLayer : public pb::Layer {

public:

	EditorLayer();

	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate(pb::Timestep ds) override;
	void OnEvent(pb::Event& event) override;
	virtual void OnImGuiRender() override;

private:

	std::unique_ptr<pb::Framebuffer> m_Framebuffer;

	bool m_ViewportActive;

	// Tracked stats
	static float m_FPS;
	static int fps_counter;

	GameLayer m_GameLayer;


};