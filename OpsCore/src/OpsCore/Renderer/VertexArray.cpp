#include "ocpch.h"

#include "VertexArray.h"
#include "RendererAPI.h"

#include "OpsCore/Platform/OpenGL/OpenGLVertexArray.h"

namespace oc {

	VertexArray* VertexArray::Create() {

		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None:
			OC_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLVertexArray();
		default:
			OC_ASSERT(false, "Unknown RendererAPI!");
			return nullptr;
		}
	}
}