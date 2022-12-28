#pragma once

namespace Oasis {
	enum class RenderBackend {
		None = 0,
		OpenGL = 1
	};

	class Renderer {
	public:
		inline static RenderBackend GetRenderBackend() {
			return backend;
		}
	private:
		static RenderBackend backend;
	};
}