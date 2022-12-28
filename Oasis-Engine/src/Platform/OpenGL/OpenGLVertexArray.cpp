#include "OasisPCH.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Oasis {
	static GLenum ShaderDataTypeToGLBaseType(ShaderDataType type) {
		switch (type) {
		case ShaderDataType::Float: return GL_FLOAT;
		case ShaderDataType::Float2: return GL_FLOAT;
		case ShaderDataType::Float3: return GL_FLOAT;
		case ShaderDataType::Float4: return GL_FLOAT;
		case ShaderDataType::Int: return GL_INT;
		case ShaderDataType::Int2: return GL_INT;
		case ShaderDataType::Int3: return GL_INT;
		case ShaderDataType::Int4: return GL_INT;
		case ShaderDataType::Mat3: return GL_FLOAT;
		case ShaderDataType::Mat4: return GL_FLOAT;
		case ShaderDataType::Boolean: return GL_BOOL;
		}

		OE_COREASSERT(false, "Can't convert unrecognized shader data type to OpenGL base type!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray() {
		glCreateVertexArrays(1, &renderId);
	}

	OpenGLVertexArray::~OpenGLVertexArray() {
		glDeleteVertexArrays(1, &renderId);
	}

	void OpenGLVertexArray::Bind() const {
		glBindVertexArray(renderId);
	}
	void OpenGLVertexArray::Unbind() const {
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& buffer) {
		OE_COREASSERT(buffer->GetLayout().GetBufferElements().size(), "Cannot bind vertex buffer missing a layout!");

		glBindVertexArray(renderId);
		buffer->Bind();

		uint32_t idx = 0;
		for(const auto& elem : buffer->GetLayout().GetBufferElements()) {
			glEnableVertexAttribArray(idx);
			glVertexAttribPointer(idx, elem.GetComponentCount(), ShaderDataTypeToGLBaseType(elem.type), elem.normalized ? GL_TRUE : GL_FALSE, buffer->GetLayout().GetStride(), (const void*)elem.offset);
			idx++;
		}
		vertexBuffers.push_back(buffer);
	}
	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& buffer) {
		glBindVertexArray(renderId);
		buffer->Bind();
		indexBuffer = buffer;
	}
}