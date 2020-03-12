#include <OpsCore.h>
#include "imgui.h"


class ExampleLayer : public oc::Layer {

public:

	ExampleLayer();

	void OnUpdate(oc::Timestep ds) override;
	void OnEvent(oc::Event& event) override;
	virtual void OnImGuiRender() override;

private:

	oc::ShaderLibrary m_ShaderLibrary;

	oc::OrthographicCameraController m_CameraController;


	std::shared_ptr<oc::Texture2D> texture;

	std::string m_CurrentShader;
	std::string m_TexturePathName = "assets/textures/checkerboard.png";
	std::string m_TextureShaderPath = "assets/shaders/ImageTexture.glsl";
	std::string m_TriangleShaderPath = "assets/shaders/TriangleShader.glsl";
	std::string m_SquareShaderPath = "assets/shaders/SquareShader.glsl";

	glm::vec3 m_RedColor = glm::vec3(0.8f, 0.2f, 0.2f);
	glm::vec3 m_BlueColor = glm::vec3(0.2f, 0.2f, 0.8f);


	// Tracked stats
	static float m_FPS;
	static int fps_counter;
};