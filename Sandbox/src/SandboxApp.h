#include <OpsCore.h>
#include "imgui.h"


class ExampleLayer : public oc::Layer {

public:

	ExampleLayer();

	void OnUpdate(oc::Timestep ds) override;
	void OnEvent(oc::Event& event) override;
	virtual void OnImGuiRender() override;

private:

	oc::OrthographicCameraController m_CameraController;

	// ------- Triangle inits ---------------------------
	float triangle_vertices[3 *3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f, 
			 0.0f, 0.5f, 0.0f, 
	};

	uint32_t triangle_indices[3] = { 0, 1, 2 };

	oc::BufferLayout triangleLayout = {
		{ oc::ShaderDataType::Float3, "a_pos"}	
	};

	std::shared_ptr<oc::VertexBuffer> triangle_vb;
	std::shared_ptr<oc::VertexArray> triangle_va;
	std::shared_ptr<oc::IndexBuffer> triangle_ib;


	// ----------- Square inits ---------------------------
	float square_vertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f
	};

	uint32_t square_indices[6] = { 0, 1, 2, 2, 3, 1 };

	oc::BufferLayout squareLayout = {
		{oc::ShaderDataType::Float3, "a_Position"}, 
		{ oc::ShaderDataType::Float2, "a_TextCoord"}
	};

	std::shared_ptr<oc::VertexBuffer> square_vb;
	std::shared_ptr<oc::VertexArray> square_va;
	std::shared_ptr<oc::IndexBuffer> square_ib;

	std::shared_ptr<oc::Shader> triangle_shader;
	std::shared_ptr<oc::Shader> square_shader;
	std::shared_ptr<oc::Shader> texture_shader;

	std::shared_ptr<oc::Texture2D> texture;

	std::string m_TexturePathName = "assets/textures/checkerboard.png";
	std::string m_TextureShaderPath = "assets/shaders/ImageTexture.glsl";
	std::string m_TriangleShaderPath = "assets/shaders/TriangleShader.glsl";
	std::string m_SquareShaderPath = "assets/shaders/SquareShader.glsl";

	glm::vec3 m_RedColor = glm::vec3(0.8f, 0.2f, 0.2f);
	glm::vec3 m_BlueColor = glm::vec3(0.2f, 0.2f, 0.8f);

};