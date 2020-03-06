#include "ocpch.h"
#include "Renderer.h"
#include "OpsCore/Platform/OpenGL/OpenGLShader.h"

namespace oc {

	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;
	int Renderer::screenWidth = int(0);
	int Renderer::screenHeight = int(0);
	float Renderer::aspectRatio = float(1.0f);

	void Renderer::BeginScene(Orthographic2DCamera& camera)
	{
		m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}
	
	void Renderer::EndScene()
	{
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}
	
	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4 transform)
	{
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Model", transform);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}