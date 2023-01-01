#pragma once

#include "VertexArray.h"

#include <glm/glm.hpp>
#include <memory>

namespace Oasis {
	class RendererAPI {
	public:
		enum class RenderBackend {
			None = 0,
			OpenGL = 1
		};

		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void ClearScreen() = 0;
		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;
		
		inline static RenderBackend GetBackend() { return backend; }
	private:
		static RenderBackend backend;
	};
}