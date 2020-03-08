#include "ocpch.h"

#include "Texture.h"
#include "Renderer.h"
#include "OpsCore/Platform/OpenGL/OpenGLTexture.h"



namespace oc {

	std::shared_ptr<Texture2D> Texture2D::Create(const std::string& path){
	
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None:
			OC_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLTexture2D>(path);
		default:
			OC_ASSERT(false, "Unknown RendererAPI!");
			return nullptr;
		}
	}
}