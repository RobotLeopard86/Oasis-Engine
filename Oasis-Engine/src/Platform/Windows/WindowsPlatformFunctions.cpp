#include "OasisPCH.h"
#include "WindowsPlatformFunctions.h"

#include <GLFW/glfw3.h>

namespace Oasis {
	PlatformFunctions* PlatformFunctions::instance = new WindowsPlatformFunctions;

	float WindowsPlatformFunctions::GetElapsedTime_Impl() {
		return glfwGetTime();
	}
}