#include <PumpkinBox.h>
#include "imgui.h"

#include "PumpkinBox/Core/Entrypoint.h"

class ExampleLayer : public pb::Layer {

public:

	ExampleLayer();

	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate(pb::Timestep ds) override;
	void OnEvent(pb::Event& event) override;
	virtual void OnImGuiRender() override;

private:

	pb::OrthographicCameraController m_CameraController;

	pb::Ref<pb::Texture2D> checkerboard_texture;
	pb::Ref<pb::Texture2D> mushroom_texture;

	std::string m_CheckerboardPath = "assets/textures/checkerboard.png";
	std::string m_MushroomPath = "assets/textures/super.png";

	glm::vec4 checkerboard_blend_color = glm::vec4(1.0f);

	// Tracked stats
	static float m_FPS;
	static int fps_counter;

};