#include "pbpch.h"
#include "Renderer2D.h"
#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>

namespace pb 
{
	struct Renderer2DStorage 
	{
		std::shared_ptr<VertexArray> m_QuadVertexArray;
		std::shared_ptr<VertexArray> m_SpriteVertexArray;

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

		float sprite_vertices[5 * 4] = {
				-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
				 0.5f, -0.5f, 0.0f, 0.25f, 0.0f,
				-0.5f,  0.5f, 0.0f, 0.0f, 0.05f,
				 0.5f,  0.5f, 0.0f, 0.25f, 0.05f
		};

		s_Data->m_QuadVertexArray = pb::VertexArray::Create();
		s_Data->m_SpriteVertexArray = pb::VertexArray::Create();

		// Setting up square VBs
		Ref<VertexBuffer> square_vb;
		Ref<VertexBuffer> sprite_vb;

		BufferLayout squareLayout = {
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float2, "a_TexCoord"}
		};

		square_vb.reset(pb::VertexBuffer::Create(square_vertices, sizeof(square_vertices)));
		square_vb->SetLayout(squareLayout);
		s_Data->m_QuadVertexArray->AddVertexBuffer(square_vb);

		sprite_vb.reset(pb::VertexBuffer::Create(sprite_vertices, sizeof(sprite_vertices)));
		sprite_vb->SetLayout(squareLayout);
		s_Data->m_SpriteVertexArray->AddVertexBuffer(sprite_vb);

		// Setting up square IBs
		uint32_t square_indices[6] = { 0, 1, 2, 2, 3, 1 };
		Ref<IndexBuffer> square_ib;

		square_ib.reset(pb::IndexBuffer::Create(square_indices, sizeof(square_indices)));
		s_Data->m_QuadVertexArray->SetIndexBuffer(square_ib);
		s_Data->m_SpriteVertexArray->SetIndexBuffer(square_ib);

		// White pixel texture - default texture
		s_Data->m_WhiteTexture = Texture2D::Create(1, 1);
		uint32_t white_texture_data = 0xffffffff;
		s_Data->m_WhiteTexture->SetData(&white_texture_data, sizeof(white_texture_data));

		// Packed all three into one shader
		//ShaderLibrary::GetInstance()->Load("assets/shaders/FlatColor.glsl");
 
		//ShaderLibrary::GetInstance()->Load("assets/shaders/Texture.glsl");
		//ShaderLibrary::GetInstance()->Get("Texture")->Bind();
		//ShaderLibrary::GetInstance()->Get("Texture")->SetInt("u_Texture", textureShaderCounter++);

		//ShaderLibrary::GetInstance()->Load("assets/shaders/TilingTexture.glsl");
		//ShaderLibrary::GetInstance()->Get("TilingTexture")->Bind();
		//ShaderLibrary::GetInstance()->Get("TilingTexture")->SetInt("u_Texture", textureShaderCounter++);


		ShaderLibrary::GetInstance()->Load("assets/shaders/ColorTexture.glsl");
		ShaderLibrary::GetInstance()->Load("assets/shaders/SpriteTexture.glsl");

		ShaderLibrary::GetInstance()->Get("ColorTexture")->Bind();
		ShaderLibrary::GetInstance()->Get("ColorTexture")->SetInt("u_Texture", 0);

		ShaderLibrary::GetInstance()->Get("SpriteTexture")->Bind();
		ShaderLibrary::GetInstance()->Get("SpriteTexture")->SetInt("u_Texture", 0);
	}

	void Renderer2D::Shutdown()
	{
		delete s_Data;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		//ShaderLibrary::GetInstance()->Get("FlatColor")->Bind();
		//ShaderLibrary::GetInstance()->Get("FlatColor")->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

		//ShaderLibrary::GetInstance()->Get("Texture")->Bind();
		//ShaderLibrary::GetInstance()->Get("Texture")->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

		//ShaderLibrary::GetInstance()->Get("TilingTexture")->Bind();
		//ShaderLibrary::GetInstance()->Get("TilingTexture")->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

		ShaderLibrary::GetInstance()->Get("ColorTexture")->Bind();
		ShaderLibrary::GetInstance()->Get("ColorTexture")->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

		ShaderLibrary::GetInstance()->Get("SpriteTexture")->Bind();
		ShaderLibrary::GetInstance()->Get("SpriteTexture")->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
	}

	void Renderer2D::EndScene()
	{
	}

	


	// Grid: height : -1 : 1 ,  width: -aspect ratio : aspect ratio
	// We want a grid with origin in bottom left corner, i.e. translate all positions by (aspect_ratio, 1)
	// Whats left is to shift the origin ( -size.x/2, -size.y/2 )
	//              +1   
	//				|
	//				|
	//				|
	//				|
	// -AR ---------|---------- AR
	//				|
	//				|
	//				|
	//				|
	//				-1

	/*
	* Transforms coordinates from (0 -> 1) by (0 -> 1) to their correct positions
	*/
	glm::vec3 normalized_to_scaled(const glm::vec3& position, const glm::vec2& size) {
		return { 2 * (position.x - 0.5f) * Renderer::aspectRatio + (abs(size.x) * Renderer::aspectRatio), 2 * (position.y - 0.5f) + abs(size.y), position.z };
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
		{
			PB_PROFILE_SCOPE("Texture binding");
			texture->Bind(); // Get image in : Pass this to uniform in texture shader
		}
		
		ShaderLibrary::GetInstance()->Get("ColorTexture")->Bind(); // Get texture in 
		ShaderLibrary::GetInstance()->Get("ColorTexture")->SetFloat4("u_Color", color);
		
		glm::mat4 rotation = glm::mat4(1.0f);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), normalized_to_scaled(position, size))
			* rotation 
			* glm::scale(glm::mat4(1.0f), { size.x*2, size.y*2, 1.0f });

		ShaderLibrary::GetInstance()->Get("ColorTexture")->SetMat4("u_Transform", transform);
		ShaderLibrary::GetInstance()->Get("ColorTexture")->SetFloat2("u_TileScale", { tileScale.x, tileScale.y });

		s_Data->m_QuadVertexArray->Bind();
		
		{
			PB_PROFILE_SCOPE("Drawing vertex array");
			RenderCommand::DrawIndexed(s_Data->m_QuadVertexArray);
		}
	}

	void Renderer2D::DrawSprite(const int& index, const glm::vec2& position, const float size, const Ref<Texture2D>& texture, int rows, int cols, const glm::vec2& tileScale, const glm::vec4& color)
	{
		DrawSprite(index, { position.x, position.y, 0.0f }, size, texture, rows, cols, tileScale, color);
	}

	void Renderer2D::DrawSprite(const int& index, const glm::vec3& position, const float size, const Ref<Texture2D>& texture, int rows, int cols, const glm::vec2& tileScale, const glm::vec4& color)
	{
		texture->Bind(); // Get image in : Pass this to uniform in texture shader

		ShaderLibrary::GetInstance()->Get("SpriteTexture")->Bind(); // Get texture in 
		ShaderLibrary::GetInstance()->Get("SpriteTexture")->SetFloat4("u_Color", color);

		glm::mat4 rotation = glm::mat4(1.0f);
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), normalized_to_scaled(position, { size, size }))
			* rotation
			* glm::scale(glm::mat4(1.0f), { size * 2, abs(size) * 2, 1.0f }
		);
		
		// Shift UV coordinates by amount dependent on parent sprite
		glm::vec2 uv_shift = { (float)(index % cols)/cols, (rows - 1 - (float)(index/cols))/rows};

		ShaderLibrary::GetInstance()->Get("SpriteTexture")->SetMat4("u_Transform", transform);
		ShaderLibrary::GetInstance()->Get("SpriteTexture")->SetFloat2("u_TileScale", { tileScale.x, tileScale.y });
		ShaderLibrary::GetInstance()->Get("SpriteTexture")->SetFloat2("u_UVShift", uv_shift);
		
		s_Data->m_SpriteVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->m_SpriteVertexArray);
	}
}
