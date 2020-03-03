#include "ocpch.h"

#include "VertexArray.h"
#include "Renderer.h"

#include "OpsCore/Platform/OpenGL/OpenGLVertexArray.h"

namespace oc {

	VertexArray* VertexArray::Create() {

		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:
			OC_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::OpenGL:
			return new OpenGLVertexArray();
		default:
			OC_ASSERT(false, "Unknown RendererAPI!");
			return nullptr;
		}
	}
}