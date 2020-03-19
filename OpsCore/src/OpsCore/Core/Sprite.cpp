#include "ocpch.h"
#include "OpsCore/Core/Sprite.h"

namespace oc {

	void Sprite::Render(const glm::vec2& position, float size, bool flip, const glm::vec2& tileScale, const glm::vec4& colorTint) {
		Render({ position.x, position.y, 0.0f }, size, flip, tileScale, colorTint);
	}

	void Sprite::Render(const glm::vec3& position, float size, bool flip, const glm::vec2& tileScale, const glm::vec4& colorTint) {
		oc::Renderer2D::DrawSprite(
			currentIndex,
			position, // position
			flip ? -1.0f*abs(size) : abs(size), // size
			m_Texture,
			textureRows,
			textureCols,
			tileScale, // tile scale
			colorTint // color tint
		);
	}

}