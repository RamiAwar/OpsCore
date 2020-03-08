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
			default: return 0;
		}
	}

	struct BufferElement {
		std::string name;
		ShaderDataType type;

		uint32_t size;
		uint32_t offset;

		bool normalized;

		// TODO: fill out default constructor
		BufferElement() {}

		BufferElement(ShaderDataType _type, const std::string& _name, bool normalized = false)
			: name(_name), type(_type), size(ShaderDataTypeSize(_type)), offset(0) {}

		uint32_t GetComponentCount() const {
			switch (type) {
				case ShaderDataType::Float:   return 1;
				case ShaderDataType::Float2:  return 2;
				case ShaderDataType::Float3:  return 3;
				case ShaderDataType::Float4:  return 4;
				
				case ShaderDataType::Mat3:    return 3*3;
				case ShaderDataType::Mat4:    return 4*4;
				
				case ShaderDataType::Int:     return 1;
				case ShaderDataType::Int2:    return 2;
				case ShaderDataType::Int3:    return 3;
				case ShaderDataType::Int4:    return 4;

				case ShaderDataType::Bool:    return 1;
				default: return 0;
			}
		}
	};

	class BufferLayout {
	public:

		// TODO: fill out default constructor
		BufferLayout() {}

		BufferLayout(const std::initializer_list<BufferElement>& elements)
			: m_Elements(elements) {
			CalculateOffsetStride();
		}
		
		inline uint32_t GetStride() const { return m_Stride; }

		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }

		// Aadd begin end iterators for quick for loop
		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }

		inline uint32_t size() {return m_Elements.size();}

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

		virtual const BufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;

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