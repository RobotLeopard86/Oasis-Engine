#pragma once

#include "OasisEngine/Rendering/RendererAPI.h"

namespace Oasis {
	class OpenGLRendererAPI : public RendererAPI {
	public:
		void SetClearColor(const glm::vec4& color) override;
		void ClearScreen() override;
		void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
	};
}