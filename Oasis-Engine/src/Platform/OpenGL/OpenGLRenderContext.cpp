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

		OE_CORE_INFO("Oasis Engine OpenGL Information:");
		OE_CORE_INFO("  Vendor: {0}", (const char*)glGetString(GL_VENDOR));
		OE_CORE_INFO("  Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		OE_CORE_INFO("  Version: {0}", (const char*)glGetString(GL_VERSION));
	}
	void OpenGLRenderContext::SwapBuffers() {
		glfwSwapBuffers(windowHandle);
	}
}