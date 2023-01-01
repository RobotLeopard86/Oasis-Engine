#include "OasisPCH.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Oasis {
	VertexArray* VertexArray::Create() {
		switch (Renderer::GetRenderBackend()) {
		case RendererAPI::RenderBackend::None:
			OE_CORE_ERROR("Null pointer will be returned from vertex array creation.");
			OE_COREASSERT(false, "Running Oasis Engine without a render backend is currently unsupported");
			return nullptr;
		case RendererAPI::RenderBackend::OpenGL: return new OpenGLVertexArray();
		}

		OE_CORE_ERROR("Null pointer will be returned from vertex array creation.");
		OE_COREASSERT(false, "A supported render backend was not recognized.");
	}
}