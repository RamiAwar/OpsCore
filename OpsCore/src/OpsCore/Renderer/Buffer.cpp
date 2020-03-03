#include "ocpch.h"
#include "Buffer.h"


#include "RendererAPI.h"
#include "OpsCore/Platform/OpenGL/OpenGLBuffer.h"

namespace oc {

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size) {

		// Decide which API being used
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None:
			OC_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLVertexBuffer(vertices, size);
		default:
			OC_ASSERT(false, "Unknown RendererAPI!");
			return nullptr;
		}
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size) {

		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None:
			OC_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;

		case RendererAPI::API::OpenGL:
			return new OpenGLIndexBuffer(indices, size);


		default:
			OC_ASSERT(false, "Unknown RendererAPI!");
			return nullptr;
		}

		return nullptr;
	}

}