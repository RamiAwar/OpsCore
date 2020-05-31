#include <PumpkinBox.h>
#include "imgui.h"

class GameLayer : public pb::Layer {

public:

	GameLayer();

	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate(pb::Timestep ds) override;
	void OnEvent(pb::Event& event) override;
	void OnRender() override;
	virtual void OnImGuiRender() override;

private:

	pb::ECS::World m_World;
	pb::ECS::Entity m_Player;


	pb::OrthographicCameraController m_CameraController;

	pb::Ref<pb::Texture2D> checkerboard_texture;
	pb::Ref<pb::Texture2D> mushroom_texture;

	std::string m_CheckerboardPath = "assets/textures/checkerboard.png";
	std::string m_MushroomPath = "assets/textures/super.png";

	glm::vec4 checkerboard_blend_color = glm::vec4(1.0f);

};