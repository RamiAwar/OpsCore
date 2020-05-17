#include "pbpch.h"

#include "VertexArray.h"
#include "RendererAPI.h"

#include "PumpkinBox/Platform/OpenGL/OpenGLVertexArray.h"

namespace pb {

	std::shared_ptr<VertexArray> VertexArray::Create() {

		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None:
			PB_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLVertexArray>();
		default:
			PB_ASSERT(false, "Unknown RendererAPI!");
			return nullptr;
		}
	}
}