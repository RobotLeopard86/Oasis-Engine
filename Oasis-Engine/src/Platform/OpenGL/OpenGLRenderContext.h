#pragma once

#include "OasisEngine/Rendering/RenderContext.h"

#include <GLFW/glfw3.h>

namespace Oasis {
	class OpenGLRenderContext : public RenderContext {
	public:
		OpenGLRenderContext(GLFWwindow* windowHandle);
		void InitContext() override;
		void SwapBuffers() override;
	private:
		GLFWwindow* windowHandle;
	};
}