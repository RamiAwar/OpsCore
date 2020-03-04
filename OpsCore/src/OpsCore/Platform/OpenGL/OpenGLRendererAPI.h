#pragma once

#include "OpsCore/Renderer/RendererAPI.h"

#include <glad/glad.h>

namespace oc {

	class OpenGLRendererAPI : public RendererAPI {

	public:

		void SetClearColor(const glm::vec4& color) {glClearColor(color.r, color.g, color.b, color.a);}
		void Clear() {glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);}
		void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray){
			glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
		}

	};
}