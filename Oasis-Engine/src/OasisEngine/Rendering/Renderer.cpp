#include "OasisPCH.h"
#include "Renderer.h"

#include "RenderJob.h"

namespace Oasis {
	bool Renderer::allowSubmissions = false;

	void Renderer::StartScene() {
		if(allowSubmissions) {
			OE_COREASSERT(false, "Cannot start scene as the current scene hasn't been concluded. Ignoring start scene call.");
			return;
		}

		allowSubmissions = true;
		RenderJob::ClearScreen();
	}
	void Renderer::ConcludeScene() {
		if (!allowSubmissions) {
			OE_COREASSERT(false, "Cannot conclude scene as no scene is currently started. Ignoring conclude scene call.");
			return;
		}

		allowSubmissions = false;
	}

	void Renderer::SubmitRawGeometry(const std::shared_ptr<VertexArray>& vertexArray) {
		if(!allowSubmissions) {
			OE_COREASSERT(false, "Cannot submit geometry when a scene is not active!");
			return;
		}

		RenderJob::DrawIndexed(vertexArray);
	}
}