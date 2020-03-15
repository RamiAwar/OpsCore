#include "ocpch.h"

#include "Texture.h"
#include "Renderer.h"
#include "OpsCore/Platform/OpenGL/OpenGLTexture.h"



namespace oc {

	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None:
			OC_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLTexture2D>(width, height);
		default:
			OC_ASSERT(false, "Unknown RendererAPI!");
			return nullptr;
		}
		
	}

	Ref<Texture2D> Texture2D::Create(const std::string& path){
	
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None:
			OC_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLTexture2D>(path);
		default:
			OC_ASSERT(false, "Unknown RendererAPI!");
			return nullptr;
		}
	}
}