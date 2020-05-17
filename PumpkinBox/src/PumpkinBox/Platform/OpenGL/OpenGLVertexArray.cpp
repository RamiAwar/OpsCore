#include "pbpch.h"

#include "PumpkinBox/Platform/OpenGL/OpenGLVertexArray.h"
#include "PumpkinBox/Platform/OpenGL/OpenGLMacros.h"
#include <glad/glad.h>

namespace pb {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
		switch (type)
		{
		case pb::ShaderDataType::Float: return GL_FLOAT;
		case pb::ShaderDataType::Float2:return GL_FLOAT;
		case pb::ShaderDataType::Float3:return GL_FLOAT;
		case pb::ShaderDataType::Float4:return GL_FLOAT;
		case pb::ShaderDataType::Mat3:return GL_FLOAT;
		case pb::ShaderDataType::Mat4:return GL_FLOAT;
		case pb::ShaderDataType::Int:return GL_INT;
		case pb::ShaderDataType::Int2:return GL_INT;
		case pb::ShaderDataType::Int3:return GL_INT;
		case pb::ShaderDataType::Int4:return GL_INT;
		case pb::ShaderDataType::Bool:return GL_BOOL;
		default:
			PB_ASSERT(false, "Unknown ShaderDataType!");
			return GL_FALSE;
		}
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		#ifdef PB_PLATFORM_MACOS
			GLCall(glGenVertexArrays(1, &m_RendererID));
		#else 
			GLCall(glCreateVertexArrays(1, &m_RendererID));
		#endif
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		GLCall(glDeleteVertexArrays(1, &m_RendererID));
	}

	void OpenGLVertexArray::Bind() const {
		GLCall(glBindVertexArray(m_RendererID));
	}

	void OpenGLVertexArray::Unbind() const {
		GLCall(glBindVertexArray(0));
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) {
		GLCall(glBindVertexArray(m_RendererID));
		vertexBuffer->Bind();

		PB_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex buffer has no layout!");

		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();

		for (const auto& element : layout) {
			GLCall(glEnableVertexAttribArray(index));
			GLCall(glVertexAttribPointer(
				index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.type),
				element.normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.offset
			));
			index++;
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) {
		GLCall(glBindVertexArray(m_RendererID));
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}
}