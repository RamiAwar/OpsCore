#include "ocpch.h"
#include "Renderer2D.h"
#include "VertexArray.h"
#include "Shader.h"
#include "OpsCore/Platform/OpenGL/OpenGLShader.h"
#include "RenderCommand.h"

namespace oc {

	struct Renderer2DStorage {
		std::shared_ptr<VertexArray> QuadVertexArray;
		std::shared_ptr<Shader> FlatColorShader;
	};

	static Renderer2DStorage* s_Data; // make pointer so we can free in shutdown


	void Renderer2D::Init()
	{

		s_Data = new Renderer2DStorage();

		// ----------- Square inits ---------------------------
		float square_vertices[5 * 4] = {
				-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
				 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
				-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
				 0.5f,  0.5f, 0.0f, 1.0f, 1.0f
		};


		s_Data->QuadVertexArray = oc::VertexArray::Create();


		// Setting up square VBs
		std::shared_ptr<VertexBuffer> square_vb;

		BufferLayout squareLayout = {
			{ShaderDataType::Float3, "a_Position"},
			{ ShaderDataType::Float2, "a_TextCoord"}
		};
		square_vb.reset(oc::VertexBuffer::Create(square_vertices, sizeof(square_vertices)));
		square_vb->SetLayout(squareLayout);
		s_Data->QuadVertexArray->AddVertexBuffer(square_vb);

		// Setting up square IBs
		uint32_t square_indices[6] = { 0, 1, 2, 2, 3, 1 };
		std::shared_ptr<IndexBuffer> square_ib;

		square_ib.reset(oc::IndexBuffer::Create(square_indices, sizeof(square_indices)));
		s_Data->QuadVertexArray->SetIndexBuffer(square_ib);

		s_Data->FlatColorShader = oc::Shader::Create("assets/shaders/FlatColor.glsl");

	}

	void Renderer2D::Shutdown()
	{
		delete s_Data;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		std::dynamic_pointer_cast<oc::OpenGLShader>(s_Data->FlatColorShader)->Bind();
		std::dynamic_pointer_cast<oc::OpenGLShader>(s_Data->FlatColorShader)->UploadUniformMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
		std::dynamic_pointer_cast<oc::OpenGLShader>(s_Data->FlatColorShader)->UploadUniformMat4("u_Transform", glm::mat4(1.0f));

	}

	void Renderer2D::EndScene()
	{
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		std::dynamic_pointer_cast<oc::OpenGLShader>(s_Data->FlatColorShader)->Bind();
		OC_TRACE("Bind shader");
		std::dynamic_pointer_cast<oc::OpenGLShader>(s_Data->FlatColorShader)->UploadUniformFloat4("u_Color", color);
		OC_TRACE("Upload uniform color");
		s_Data->QuadVertexArray->Bind();
		OC_TRACE("Bind VA");
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
		OC_TRACE("Draw Indexed");
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
	}


}
