#include "pbpch.h"
#include "PumpkinBox/Platform/OpenGL/OpenGLBuffer.h"
#include "PumpkinBox/Platform/OpenGL/OpenGLMacros.h"

#include <glad/glad.h>


/////////////////////////////////////////////////////////////////////
// --------------------- Vertex Buffer ------------------------------
/////////////////////////////////////////////////////////////////////
pb::OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
	: m_Size(size)
{
	
	#ifdef PB_PLATFORM_MACOS
		GLCall(glGenBuffers(1, &m_RendererID));
	#else 
		GLCall(glCreateBuffers(1, &m_RendererID));
	#endif
	
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
		GLCall(glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW));
}

pb::OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_RendererID));
}

void pb::OpenGLVertexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void pb::OpenGLVertexBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}




////////////////////////////////////////////////////////////////
//  -------------------------  Index Buffer --------------------
////////////////////////////////////////////////////////////////
pb::OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)
	: m_Count(count)
{
#ifdef PB_PLATFORM_MACOS
	GLCall(glGenBuffers(1, &m_RendererID));
#else
	GLCall(glCreateBuffers(1, &m_RendererID));
#endif

	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW));
}

pb::OpenGLIndexBuffer::~OpenGLIndexBuffer() {
	GLCall(glDeleteBuffers(1, &m_RendererID));
}

void pb::OpenGLIndexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}

void pb::OpenGLIndexBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

