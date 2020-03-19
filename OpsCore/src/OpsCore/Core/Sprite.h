#pragma once

#include "OpsCore/Core/Log.h"
#include "OpsCore/Core/Core.h"
#include "OpsCore/Renderer/Texture.h"
#include "OpsCore/Renderer/Renderer2D.h"
#include <glm/glm.hpp>

namespace oc {

	class Sprite {

	public:

		Sprite(const std::string& path, int rows, int cols, int nFrames) 
			: m_TexturePath(path), textureRows(rows), textureCols(cols), totalFrames(nFrames)
		{
			m_Texture = oc::Texture2D::Create(path);
		}

		void Render(const glm::vec2& position, float size, bool flip=false,
			const glm::vec2& tileScale = { 1.0f, 1.0f }, 
			const glm::vec4& colorTint = glm::vec4(1.0f));

	private:
		oc::Ref<oc::Texture2D> m_Texture;
		std::string m_TexturePath;

	public:
		int textureRows, textureCols, totalFrames;
		int currentIndex;


	};

}