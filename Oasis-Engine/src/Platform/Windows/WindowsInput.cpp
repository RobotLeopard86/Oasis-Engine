#include "OasisPCH.h"
#include "WindowsInput.h"
#include "OasisEngine/Application.h"

#include <GLFW/glfw3.h>

namespace Oasis {

	Input* WindowsInput::instance = new WindowsInput();

	bool WindowsInput::IsKeyPressed_Impl(int keycode) {
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}
	bool WindowsInput::IsMouseButtonPressed_Impl(int button) {
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}
	std::pair<float, float> WindowsInput::GetMousePos_Impl() {
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos_in;
		double ypos_in;
		glfwGetCursorPos(window, &xpos_in, &ypos_in);
		float xpos = (float)xpos_in;
		float ypos = (float)ypos_in;
		return std::pair<float, float>(xpos, ypos);
	}
	float WindowsInput::GetMouseX_Impl() {
		auto[x, y] = GetMousePos_Impl();
		return x;
	}
	float WindowsInput::GetMouseY_Impl() {
		auto[x, y] = GetMousePos_Impl();
		return y;
	}
}