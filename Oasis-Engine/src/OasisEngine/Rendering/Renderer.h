#pragma once

#include "RendererAPI.h"
#include "Cameras/Camera.h"
#include "Shader.h"

#include <glm/glm.hpp>

namespace Oasis {
	class Renderer {
	public:
		static void StartScene(Camera& mainCamera);
		static void ConcludeScene();

		static void SubmitRawGeometry(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const glm::vec3& transform);

		inline static RendererAPI::RenderBackend GetRenderBackend() { return RendererAPI::GetBackend(); }
	private:
		static bool allowSubmissions;
		static glm::mat4 viewProjectionMatrix;
	};
}