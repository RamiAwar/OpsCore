#include "ocpch.h"
#include "OpsCore/Platform/OpenGL/OpenGLBuffer.h"
#include "OpsCore/Platform/OpenGL/OpenGLMacros.h"

#include <glad/glad.h>


/////////////////////////////////////////////////////////////////////
// --------------------- Vertex Buffer ------------------------------
/////////////////////////////////////////////////////////////////////
oc::OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
{
	
	#ifdef OC_PLATFORM_MACOS
		GLCall(glGenBuffers(1, &m_RendererID));
	#else 
		GLCall(glCreateBuffers(1, &m_RendererID));
	#endif
	
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
		GLCall(glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW));
}

oc::OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_RendererID));
}

void oc::OpenGLVertexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void oc::OpenGLVertexBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}




////////////////////////////////////////////////////////////////
//  -------------------------  Index Buffer --------------------
////////////////////////////////////////////////////////////////
oc::OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)
	: m_Count(count)
{
#ifdef OC_PLATFORM_MACOS
	GLCall(glGenBuffers(1, &m_RendererID));
#else
	GLCall(glCreateBuffers(1, &m_RendererID));
#endif

	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW));
}

oc::OpenGLIndexBuffer::~OpenGLIndexBuffer() {
	GLCall(glDeleteBuffers(1, &m_RendererID));
}

void oc::OpenGLIndexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}

void oc::OpenGLIndexBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

