#pragma once

#include "PumpkinBox/Renderer/RendererAPI.h"

#include <glad/glad.h>

namespace pb {

	class OpenGLRendererAPI : public RendererAPI {

	public:

		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
		virtual void Init() override;

		virtual void Clear() override;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;


	};
}