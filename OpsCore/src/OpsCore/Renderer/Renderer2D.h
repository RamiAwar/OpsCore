#pragma once

#include "Cameras/OrthographicCamera.h"
#include "OpsCore/Renderer/Texture.h"
#include "OpsCore/Renderer/Renderer.h"

namespace oc {

	class Renderer2D {

	public:

		static void Init();
		static void Shutdown();

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();

		// Primitives
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color = glm::vec4(1.0f));
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color = glm::vec4(1.0f));
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec2& tileScale = { 1.0f, 1.0f }, const glm::vec4& color = glm::vec4(1.0f));
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec2& tileScale = { 1.0f, 1.0f }, const glm::vec4& color = glm::vec4(1.0f));

		static void DrawSprite(const int& index, const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec2& tileScale = { 1.0f, 1.0f }, const glm::vec4& color = glm::vec4(1.0f));
		static void DrawSprite(const int& index, const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec2& tileScale = { 1.0f, 1.0f }, const glm::vec4& color = glm::vec4(1.0f));

	};
}