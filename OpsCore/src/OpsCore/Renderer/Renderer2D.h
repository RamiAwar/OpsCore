#pragma once

#include "Cameras/OrthographicCamera.h"
#include "OpsCore/Renderer/Texture.h"

namespace oc {

	class Renderer2D {

	public:

		static void Init();
		static void Shutdown();

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();

		// Primitives

		// TODO: Add vec3 input overload so we have Z-index based sorting for rendering layers
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture);
		static void DrawQuadTile(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture);
		static void DrawQuadTile(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture);

	};
}