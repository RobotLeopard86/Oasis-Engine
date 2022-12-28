#include "OasisPCH.h"
#include "Buffer.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Oasis {
	VertexBuffer::~VertexBuffer() {}
	IndexBuffer::~IndexBuffer() {}

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size) {
		switch (Renderer::GetRenderBackend()) {
		case RenderBackend::None:
			OE_CORE_ERROR("Null pointer will be returned from vertex buffer creation.");
			OE_COREASSERT(false, "Running Oasis Engine without a render backend is currently unsupported");
			return nullptr;
		case RenderBackend::OpenGL: return new OpenGLVertexBuffer(vertices, size);
		}

		OE_CORE_ERROR("Null pointer will be returned from vertex buffer creation.");
		OE_COREASSERT(false, "A supported render backend was not recognized.");
	}
	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size) {
		switch (Renderer::GetRenderBackend()) {
		case RenderBackend::None:
			OE_CORE_ERROR("Null pointer will be returned from index buffer creation.");
			OE_COREASSERT(false, "Running Oasis Engine without a render backend is currently unsupported");
			return nullptr;
		case RenderBackend::OpenGL: return new OpenGLIndexBuffer(indices, size);
		}

		OE_CORE_ERROR("Null pointer will be returned from index buffer creation.");
		OE_COREASSERT(false, "A supported render backend was not recognized.");
	}
}