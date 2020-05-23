#pragma once

#include "PumpkinBox/Core/Log.h"
#include "PumpkinBox/Core/Core.h"
#include "PumpkinBox/Renderer/Texture.h"
#include "PumpkinBox/Renderer/Renderer2D.h"
#include <glm/glm.hpp>

namespace pb {

	class Sprite {

	public:

		Sprite(const std::string& path, int rows, int cols, int nFrames)
			: m_TexturePath(path), textureRows(rows), textureCols(cols), totalFrames(nFrames), currentIndex(0)
		{
			m_Texture = pb::Texture2D::Create(path);
		}

		void Render(const glm::vec2& position, float size, bool flip = false,
			const glm::vec2& tileScale = { 1.0f, 1.0f },
			const glm::vec4& colorTint = glm::vec4(1.0f));

		void Render(const glm::vec3& position, float size, bool flip=false,
			const glm::vec2& tileScale = { 1.0f, 1.0f }, 
			const glm::vec4& colorTint = glm::vec4(1.0f));

	private:
		pb::Ref<pb::Texture2D> m_Texture;
		std::string m_TexturePath;

	public:
		int textureRows, textureCols, totalFrames;
		int currentIndex;


	};

}