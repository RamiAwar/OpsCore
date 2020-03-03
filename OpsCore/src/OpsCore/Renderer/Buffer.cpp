#include "ocpch.h"
#include "Buffer.h"


#include "Renderer.h"
#include "OpsCore/Platform/OpenGL/OpenGLBuffer.h"

namespace oc {

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size) {

		// Decide which API being used
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:
			OC_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::OpenGL:
			return new OpenGLVertexBuffer(vertices, size);
		default:
			OC_ASSERT(false, "Unknown RendererAPI!");
			return nullptr;
		}
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size) {

		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:
			OC_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;

		case RendererAPI::OpenGL:
			return new OpenGLIndexBuffer(indices, size);


		default:
			OC_ASSERT(false, "Unknown RendererAPI!");
			return nullptr;
		}

		return nullptr;
	}

}