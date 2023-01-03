#include "OasisPCH.h"
#include "Renderer.h"

#include "RenderJob.h"

namespace Oasis {
	bool Renderer::allowSubmissions = false;
	glm::mat4 Renderer::viewProjectionMatrix = glm::mat4(0.0f);

	void Renderer::StartScene(Camera& mainCamera) {
		if(allowSubmissions) {
			OE_COREASSERT(false, "Cannot start scene as the current scene hasn't been concluded. Ignoring start scene call.");
			return;
		}

		allowSubmissions = true;
		viewProjectionMatrix = mainCamera.GetViewProjectionMatrix();
		RenderJob::ClearScreen();
	}
	void Renderer::ConcludeScene() {
		if (!allowSubmissions) {
			OE_COREASSERT(false, "Cannot conclude scene as no scene is currently started. Ignoring conclude scene call.");
			return;
		}

		allowSubmissions = false;
		viewProjectionMatrix = glm::mat4(0.0f);
	}

	void Renderer::SubmitRawGeometry(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader) {
		if(!allowSubmissions) {
			OE_COREASSERT(false, "Cannot submit geometry when a scene is not active!");
			return;
		}

		shader->Bind();
		shader->UploadUniformMat4("vpm", viewProjectionMatrix);
		vertexArray->Bind();
		RenderJob::DrawIndexed(vertexArray);
	}
}