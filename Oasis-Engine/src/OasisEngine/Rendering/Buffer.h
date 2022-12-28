#pragma once

namespace Oasis {
	enum class ShaderDataType {
		None = 0,
		Float, Float2, Float3, Float4,
		Int, Int2, Int3, Int4,
		Mat3, Mat4,
		Boolean
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type) {
		switch(type) {
		case ShaderDataType::Float: return 4;
		case ShaderDataType::Float2: return 8;
		case ShaderDataType::Float3: return 12;
		case ShaderDataType::Float4: return 16;
		case ShaderDataType::Int: return 4;
		case ShaderDataType::Int2: return 8;
		case ShaderDataType::Int3: return 12;
		case ShaderDataType::Int4: return 16;
		case ShaderDataType::Mat3: return 36;
		case ShaderDataType::Mat4: return 64;
		case ShaderDataType::Boolean: return 1;
		}

		OE_COREASSERT(false, "Can't convert unrecognized shader data type to size!");
		return 0;
	}

	struct BufferElement {
		std::string name;
		uint32_t offset;
		uint32_t size;
		ShaderDataType type;
		bool normalized;

		BufferElement() {}

		BufferElement(ShaderDataType type, std::string name, bool normalized = false)
			: name(name), type(type), size(ShaderDataTypeSize(type)), offset(0), normalized(normalized) {}

		uint32_t GetComponentCount() const {
			switch(type) {
			case ShaderDataType::Float: return 1;
			case ShaderDataType::Float2: return 2;
			case ShaderDataType::Float3: return 3;
			case ShaderDataType::Float4: return 4;
			case ShaderDataType::Int: return 1;
			case ShaderDataType::Int2: return 2;
			case ShaderDataType::Int3: return 3;
			case ShaderDataType::Int4: return 4;
			case ShaderDataType::Mat3: return 9;
			case ShaderDataType::Mat4: return 16;
			case ShaderDataType::Boolean: return 1;
			}

			OE_COREASSERT(false, "Can't convert unrecognized shader data type to component count!");
			return 0;
		}
	};

	class BufferLayout {
	public:
		BufferLayout() {}

		BufferLayout(const std::initializer_list<BufferElement>& elements)
			: elements(elements) {
			CalculateStrideAndOffset();
		}

		inline const std::vector<BufferElement>& GetBufferElements() const { return elements; }
		inline uint32_t GetStride() const { return stride; }

		std::vector<BufferElement>::iterator begin() { return elements.begin(); }
		std::vector<BufferElement>::iterator end() { return elements.end(); }
	private:
		std::vector<BufferElement> elements;
		uint32_t stride;

		void CalculateStrideAndOffset() {
			uint32_t offset = 0;
			stride = 0;
			for(auto& elem : elements) {
				elem.offset = offset;
				offset += elem.size;
				stride += elem.size;
			}
		}
	};

	class VertexBuffer {
	public:
		virtual ~VertexBuffer();

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetLayout(const BufferLayout& newLayout) = 0;
		virtual const BufferLayout& GetLayout() const = 0;

		static VertexBuffer* Create(float* vertices, uint32_t size);
	};

	class IndexBuffer {
	public:
		virtual ~IndexBuffer();

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetCount() const = 0;

		static IndexBuffer* Create(uint32_t* indices, uint32_t size);
	};
}