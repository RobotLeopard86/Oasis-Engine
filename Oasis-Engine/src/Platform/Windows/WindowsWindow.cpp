#include "OasisPCH.h"
#include "WindowsWindow.h"

namespace Oasis {
	static bool glfwInitialized = false;

	Window* Window::NewWindow(const WindowProperties& props) {
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProperties& props) {
		Init(props);
	}

	WindowsWindow::~WindowsWindow() {
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProperties& props) {
		windowData.title = props.title;
		windowData.width = props.width;
		windowData.height = props.height;

		OASISCORE_INFO("Creating window for application \"{0}\" at size {1}x{2}...", props.title, props.width, props.height);

		if(!glfwInitialized) {
			//Note: Implement glfwTerminate when system shuts down.
			int success = glfwInit();
			COREASSERT(success, "GLFW refused to initialize!");

			glfwInitialized = true;
		}

		window = glfwCreateWindow((int)props.width, (int)props.height, windowData.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(window);
		glfwSetWindowUserPointer(window, &windowData);
		SetVSyncEnabled(true);
	}

	void WindowsWindow::Shutdown() {
		OASISCORE_INFO("App window shutting down...");
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void WindowsWindow::OnUpdate() {
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	void WindowsWindow::SetVSyncEnabled(bool enabled) {
		if (enabled) {
			glfwSwapInterval(1);
		}
		else {
			glfwSwapInterval(0);
		}

		windowData.useVSync = enabled;
	}

	bool WindowsWindow::IsVSyncEnabled() const {
		return windowData.useVSync;
	}

	bool WindowsWindow::ShouldWindowClose() {
		return glfwWindowShouldClose(window);
	}
}