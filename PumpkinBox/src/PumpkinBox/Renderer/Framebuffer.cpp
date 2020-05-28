#include "pbpch.h"
#include "Framebuffer.h"

#include "PumpkinBox/Platform/OpenGL/OpenGLFramebuffer.h"

namespace pb 
{
	Framebuffer* pb::Framebuffer::Create(uint32_t width, uint32_t height, FramebufferFormat format)
	{
		Framebuffer* result = nullptr;
		
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None:
			PB_ERROR(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			result = new OpenGLFramebuffer(width, height, format);
		}

		return result;
	}
}