#pragma once

#include "RendererAPI.h"

namespace Oasis {
	class Renderer {
	public:
		static void StartScene();
		static void ConcludeScene();

		static void SubmitRawGeometry(const std::shared_ptr<VertexArray>& vertexArray);

		inline static RendererAPI::RenderBackend GetRenderBackend() { return RendererAPI::GetBackend(); }
	private:
		static bool allowSubmissions;
	};
}