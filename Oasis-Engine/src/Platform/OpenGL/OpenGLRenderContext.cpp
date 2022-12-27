#include "OasisPCH.h"
#include "OpenGLRenderContext.h"

#include <glad/glad.h>

namespace Oasis {
	OpenGLRenderContext::OpenGLRenderContext(GLFWwindow* windowHandle)
		: windowHandle(windowHandle) {
		OE_COREASSERT(windowHandle, "Couldn't start OpenGL rendering context, the provided window handle is null.");
	}

	void OpenGLRenderContext::InitContext() {
		glfwMakeContextCurrent(windowHandle);
		int gladStatus = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		OE_COREASSERT(gladStatus, "Glad refused to initialize!");
	}
	void OpenGLRenderContext::SwapBuffers() {
		glfwSwapBuffers(windowHandle);
	}
}