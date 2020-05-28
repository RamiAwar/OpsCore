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

		FramebufferPool::GetGlobal()->Add(result);
		return result;
	}

	FramebufferPool* FramebufferPool::s_Instance = new FramebufferPool;

	FramebufferPool::FramebufferPool(uint32_t max_framebuffers) {}

	FramebufferPool::~FramebufferPool() {}

	std::weak_ptr<Framebuffer> FramebufferPool::AllocateBuffer() {
		return std::weak_ptr<Framebuffer>();
	}

	void FramebufferPool::Add(Framebuffer* framebuffer) {
		m_Pool.push_back(framebuffer);
	}

}