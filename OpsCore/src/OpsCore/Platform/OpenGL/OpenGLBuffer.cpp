#include "ocpch.h"
#include "OpenGLBuffer.h"

#include <glad/glad.h>


/////////////////////////////////////////////////////////////////////
// --------------------- Vertex Buffer ------------------------------
/////////////////////////////////////////////////////////////////////
oc::OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
{
	
	#ifdef OC_PLATFORM_MAC
	glGenBuffers(1, &m_RendererID);
	#else 
	glCreateBuffers(1, &m_RendererID);
	#endif
	
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

oc::OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
	glDeleteBuffers(1, &m_RendererID);
}

void oc::OpenGLVertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void oc::OpenGLVertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}




////////////////////////////////////////////////////////////////
//  -------------------------  Index Buffer --------------------
////////////////////////////////////////////////////////////////
oc::OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)
	: m_Count(count)
{
#ifdef OC_PLATFORM_MACOS
	glGenBuffers(1, &m_RendererID);
#else
	glCreateBuffers(1, &m_RendererID);
#endif

	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
}

oc::OpenGLIndexBuffer::~OpenGLIndexBuffer() {
	glDeleteBuffers(1, &m_RendererID);
}

void oc::OpenGLIndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void oc::OpenGLIndexBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

