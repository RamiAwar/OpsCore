#include "ocpch.h"
#include "OpenGLRendererAPI.h"

void oc::OpenGLRendererAPI::Init() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	OC_TRACE("OpenGLRendererAPI Init");
}

void oc::OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
{
	OC_TRACE("Set clear color");
	glClearColor(color.r, color.g, color.b, color.a);
}

void oc::OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
	glViewport(x, y, width, height);
}

void oc::OpenGLRendererAPI::Clear()
{
	OC_TRACE("Clear screen");
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void oc::OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
{
	glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
}
