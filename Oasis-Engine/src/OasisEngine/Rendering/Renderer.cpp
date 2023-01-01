#include "OasisPCH.h"
#include "Renderer.h"

#include "RenderJob.h"

namespace Oasis {
	void Renderer::StartScene() {
		if(allowSubmissions) {
			OE_CORE_WARN("Cannot start scene before current scene is finished. Ignoring start scene call.");
			return;
		}

		allowSubmissions = true;
	}
	void Renderer::ConcludeScene() {
		if (!allowSubmissions) {
			OE_CORE_WARN("Cannot conclude scene as no scene is currently started. Ignoring conclude scene call.");
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