#pragma once

namespace Oasis {
	class RenderContext {
	public:
		virtual void InitContext() = 0;
		virtual void SwapBuffers() = 0;
	};
}