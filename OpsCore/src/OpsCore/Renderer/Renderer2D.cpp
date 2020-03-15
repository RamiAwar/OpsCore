#include "ocpch.h"
#include "Renderer2D.h"
#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>

namespace oc {

	struct Renderer2DStorage {
		std::shared_ptr<VertexArray> m_QuadVertexArray;

		ShaderLibrary m_ShaderLibrary;

		Ref<Texture2D> m_WhiteTexture;

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


		s_Data->m_QuadVertexArray = oc::VertexArray::Create();


		// Setting up square VBs
		Ref<VertexBuffer> square_vb;

		BufferLayout squareLayout = {
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float2, "a_TexCoord"}
		};

		square_vb.reset(oc::VertexBuffer::Create(square_vertices, sizeof(square_vertices)));
		square_vb->SetLayout(squareLayout);
		s_Data->m_QuadVertexArray->AddVertexBuffer(square_vb);

		// Setting up square IBs
		uint32_t square_indices[6] = { 0, 1, 2, 2, 3, 1 };
		Ref<IndexBuffer> square_ib;

		square_ib.reset(oc::IndexBuffer::Create(square_indices, sizeof(square_indices)));
		s_Data->m_QuadVertexArray->SetIndexBuffer(square_ib);

		// White pixel texture - default texture
		s_Data->m_WhiteTexture = Texture2D::Create(1, 1);
		uint32_t white_texture_data = 0xffffffff;
		s_Data->m_WhiteTexture->SetData(&white_texture_data, sizeof(white_texture_data));


		// Packed all three into one shader
		//s_Data->m_ShaderLibrary.Load("assets/shaders/FlatColor.glsl");
 
		//s_Data->m_ShaderLibrary.Load("assets/shaders/Texture.glsl");
		//s_Data->m_ShaderLibrary.Get("Texture")->Bind();
		//s_Data->m_ShaderLibrary.Get("Texture")->SetInt("u_Texture", textureShaderCounter++);

		//s_Data->m_ShaderLibrary.Load("assets/shaders/TilingTexture.glsl");
		//s_Data->m_ShaderLibrary.Get("TilingTexture")->Bind();
		//s_Data->m_ShaderLibrary.Get("TilingTexture")->SetInt("u_Texture", textureShaderCounter++);

		s_Data->m_ShaderLibrary.Load("assets/shaders/ColorTexture.glsl");
		s_Data->m_ShaderLibrary.Get("ColorTexture")->Bind();
		s_Data->m_ShaderLibrary.Get("ColorTexture")->SetInt("u_Texture", 0);

	}

	void Renderer2D::Shutdown()
	{
		delete s_Data;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		//s_Data->m_ShaderLibrary.Get("FlatColor")->Bind();
		//s_Data->m_ShaderLibrary.Get("FlatColor")->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

		//s_Data->m_ShaderLibrary.Get("Texture")->Bind();
		//s_Data->m_ShaderLibrary.Get("Texture")->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

		//s_Data->m_ShaderLibrary.Get("TilingTexture")->Bind();
		//s_Data->m_ShaderLibrary.Get("TilingTexture")->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

		s_Data->m_ShaderLibrary.Get("ColorTexture")->Bind();
		s_Data->m_ShaderLibrary.Get("ColorTexture")->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

	}

	void Renderer2D::EndScene()
	{
	}

	




	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, s_Data->m_WhiteTexture, glm::vec2(1.0f), color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad(position, size, s_Data->m_WhiteTexture, glm::vec2(1.0f), color);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec2& tileScale, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, texture, tileScale, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec2& tileScale, const glm::vec4& color)
	{
		texture->Bind(); // Get image in : Pass this to uniform in texture shader

		s_Data->m_ShaderLibrary.Get("ColorTexture")->Bind(); // Get texture in 
		s_Data->m_ShaderLibrary.Get("ColorTexture")->SetFloat4("u_Color", color);
		
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), /* add rotation here */{ size.x, size.y, 1.0f });
		
		s_Data->m_ShaderLibrary.Get("ColorTexture")->SetMat4("u_Transform", transform);
		s_Data->m_ShaderLibrary.Get("ColorTexture")->SetFloat2("u_TileScale", { tileScale.x, tileScale.y });

		s_Data->m_QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->m_QuadVertexArray);
	}




}
