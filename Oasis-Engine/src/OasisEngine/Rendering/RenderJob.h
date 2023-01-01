#pragma once

#include "RendererAPI.h"

#include <glm/glm.hpp>

namespace Oasis {
	class RenderJob {
	public:
		inline static void SetClearColor(const glm::vec4& color) {
			backendAPI->SetClearColor(color);
		}

		inline static void ClearScreen() {
			backendAPI->ClearScreen();
		}

		inline static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) {
			backendAPI->DrawIndexed(vertexArray);
		}
	private:
		static RendererAPI* backendAPI;
	};
}