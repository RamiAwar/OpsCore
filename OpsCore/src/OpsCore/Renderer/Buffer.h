#pragma once

namespace oc {

	enum class ShaderDataType {
		None = 0, 
		Float, 
		Float2, 
		Float3, 
		Float4, 
		Mat3,
		Mat4,
		Int,
		Int2,
		Int3,
		Int4,
		Bool
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type) {
		switch (type) {
			case ShaderDataType::Float:   return sizeof(float);
			case ShaderDataType::Float2:  return 2*sizeof(float);
			case ShaderDataType::Float3:  return 3*sizeof(float);
			case ShaderDataType::Float4:  return 4*sizeof(float);
			case ShaderDataType::Mat3:    return 3*3*sizeof(float);
			case ShaderDataType::Mat4:    return 4*4*sizeof(float);
			case ShaderDataType::Bool:    return 1;
			case ShaderDataType::Int:     return sizeof(float);
			case ShaderDataType::Int2:    return 2*sizeof(float);
			case ShaderDataType::Int3:    return 3*sizeof(float);
			case ShaderDataType::Int4:    return 4*sizeof(float);
		}
	}

	struct BufferElement {
		std::string name;
		ShaderDataType type;

		uint32_t size;
		uint32_t offset;

		BufferElement(ShaderDataType _type, const std::string& _name)
			: name(_name), type(_type), size(ShaderDataTypeSize(_type)), offset(0) 
		{
		
		}
	};

	class BufferLayout {
	public:

		BufferLayout(const std::initializer_list<BufferElement>& elements)
			: m_Elements(elements) {
			CalculateOffsetStride();
		}
	
		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }

	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride = 0;

		void CalculateOffsetStride() {
			uint32_t offset = 0;
			m_Stride = 0;
			for (auto& element : m_Elements) {
				element.offset = offset;
				offset += element.size;
				m_Stride += element.size;
			}
		}
	};

	class VertexBuffer {
	public:

		virtual ~VertexBuffer() {};

		//virtual void SetData(v);

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static VertexBuffer* Create(float* vertices, uint32_t size);
	};


	class IndexBuffer {
	public:

		virtual ~IndexBuffer() {};

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;


		virtual uint32_t GetCount() const = 0;

		static IndexBuffer* Create(uint32_t* indices, uint32_t size);
	};

}