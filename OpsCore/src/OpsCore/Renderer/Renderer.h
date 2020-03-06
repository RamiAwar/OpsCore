#pragma once 

#include "RenderCommand.h"
#include "Shader.h"
#include "Cameras/Orthographic2DCamera.h"

namespace oc {

	class Renderer {

	public:
		static int screenWidth;
		static int screenHeight;
		static float aspectRatio;

	public:
		static void BeginScene(Orthographic2DCamera& camera);
		static void EndScene();

		static void OnWindowResize(uint32_t width, uint32_t height);

		static void Submit(const std::shared_ptr<Shader>& shader, 
			const std::shared_ptr<VertexArray>& vertexArray, 
			const glm::mat4 transform = glm::mat4(1.0f));
	
	private:
		struct SceneData {
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;

	};
}