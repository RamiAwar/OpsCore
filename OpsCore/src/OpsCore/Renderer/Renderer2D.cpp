#include "ocpch.h"
#include "Renderer2D.h"
#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>

namespace oc {

	struct Renderer2DStorage {
		std::shared_ptr<VertexArray> QuadVertexArray;
		std::shared_ptr<Shader> FlatColorShader;
		Ref<Shader> TextureShader;
		Ref<Shader> TextureTileShader;
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
			{ShaderDataType::Float2, "a_TexCoord"}
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

		s_Data->TextureShader = oc::Shader::Create("assets/shaders/Texture.glsl");
		s_Data->TextureShader->Bind();
		s_Data->TextureShader->SetInt("u_Texture", 0);

		s_Data->TextureTileShader = oc::Shader::Create("assets/shaders/TilingTexture.glsl");
		s_Data->TextureTileShader->Bind();
		s_Data->TextureTileShader->SetInt("u_Texture", 0);

	}

	void Renderer2D::Shutdown()
	{
		delete s_Data;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		s_Data->FlatColorShader->Bind();
		s_Data->FlatColorShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
	
		s_Data->TextureShader->Bind();
		s_Data->TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

		s_Data->TextureTileShader->Bind();
		s_Data->TextureTileShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
	}

	void Renderer2D::EndScene()
	{
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		s_Data->FlatColorShader->Bind();
		s_Data->FlatColorShader->SetFloat4("u_Color", color);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), /* add rotation here */{ size.x, size.y, 1.0f });
		s_Data->FlatColorShader->SetMat4("u_Transform", transform);


		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, texture);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture)
	{
		s_Data->TextureShader->Bind(); // Get texture in 

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), /* add rotation here */{ size.x, size.y, 1.0f });
		s_Data->TextureShader->SetMat4("u_Transform", transform); 

		texture->Bind(); // Get image in : Pass this to uniform in texture shader

		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}




	void Renderer2D::DrawQuadTile(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture)
	{
		DrawQuadTile({ position.x, position.y, 0.0f }, size, texture);
	}

	void Renderer2D::DrawQuadTile(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture)
	{
		s_Data->TextureTileShader->Bind(); // Get texture in 

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), /* add rotation here */{ size.x, size.y, 1.0f });
		s_Data->TextureTileShader->SetMat4("u_Transform", transform);

		texture->Bind(); // Get image in : Pass this to uniform in texture shader

		s_Data->TextureTileShader->SetFloat2("u_TileScale", { size.x, size.y });


		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}




}
