#include "ocpch.h"

#include "Shader.h"
#include "RendererAPI.h"

#include "OpsCore/Platform/OpenGL/OpenGLShader.h"

namespace oc {
	Shader* Shader::Create(const std::string& filepath)
	{
		switch (RendererAPI::GetAPI()) {
		case RendererAPI::API::None:
			OC_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLShader(filepath);
		default:
			OC_ASSERT(false, "Unknown RendererAPI!");
			return nullptr;
		}
		return nullptr;
	}
	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc) {

		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None:
			OC_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLShader(vertexSrc, fragmentSrc);
		default:
			OC_ASSERT(false, "Unknown RendererAPI!");
			return nullptr;
		} 
	}
}