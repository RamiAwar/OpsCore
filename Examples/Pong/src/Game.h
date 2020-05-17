#include <PumpkinBox.h>
#include "imgui.h"


class Game : public pb::Layer {

public:

	Game();

	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate(pb::Timestep ds) override;
	void OnEvent(pb::Event& event) override;
	virtual void OnImGuiRender() override;

private:

	pb::ShaderLibrary m_ShaderLibrary;

	pb::OrthographicCameraController m_CameraController;

	pb::Ref<pb::Texture2D> checkerboard_texture;
	pb::Ref<pb::Texture2D> mushroom_texture;



	// Tracked stats
	static float m_FPS;
	static int fps_counter;

};