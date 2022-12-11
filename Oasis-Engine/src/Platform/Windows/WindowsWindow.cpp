#include "OasisPCH.h"
#include "WindowsWindow.h"

#include "OasisEngine/Events/ApplicationEvent.h"
#include "OasisEngine/Events/MouseEvent.h"
#include "OasisEngine/Events/KeyEvent.h"

#include <glad/glad.h>

namespace Oasis {
	static bool glfwInitialized = false;

	static void GLFWErrorCallback(int errorCode, const char* errorDescription) {
		OE_CORE_ERROR("GLFW error, code {0}. Reason: {1}", errorCode, errorDescription);
	}

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

		OE_CORE_INFO("Creating window for application \"{0}\" at size {1}x{2}...", props.title, props.width, props.height);

		if(!glfwInitialized) {
			//Note: Implement glfwTerminate when system shuts down.
			int success = glfwInit();
			OE_COREASSERT(success, "GLFW refused to initialize!");

			glfwSetErrorCallback(GLFWErrorCallback);

			glfwInitialized = true;
		}

		window = glfwCreateWindow((int)props.width, (int)props.height, windowData.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(window);
		int gladStatus = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		OE_COREASSERT(gladStatus, "Glad refused to initialize!");
		glfwSetWindowUserPointer(window, &windowData);
		SetVSyncEnabled(true);

		glfwSetWindowSizeCallback(window, [](GLFWwindow* lambdaWindow, int lambdaWidth, int lambdaHeight) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(lambdaWindow);
			WindowResizeEvent event(lambdaWidth, lambdaHeight);
			data.width = lambdaWidth;
			data.height = lambdaHeight;
			data.callback(event);
		});

		glfwSetWindowCloseCallback(window, [](GLFWwindow* lambdaWindow) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(lambdaWindow);
			WindowCloseEvent event{};
			data.callback(event);
		});

		glfwSetCharCallback(window, [](GLFWwindow* lambdaWindow, unsigned int lambdaChar) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(lambdaWindow);
			KeyTypedEvent event(lambdaChar);
			data.callback(event);
		});

		glfwSetKeyCallback(window, [](GLFWwindow* lambdaWindow, int lambdaKey, int lambdaScancode, int lambdaAction, int lambdaModifiers) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(lambdaWindow);
			switch (lambdaAction) {
			case GLFW_PRESS: {
				KeyPressedEvent event(lambdaKey, 0);
				data.callback(event);
				break;
			}
			case GLFW_RELEASE: {
				KeyReleasedEvent event(lambdaKey);
				data.callback(event);
				break;
			}
			case GLFW_REPEAT: {
				//Note: GLFW has no repeat count. 1 is hardcoded. Repeat count may later be extractable.
				KeyPressedEvent event(lambdaKey, 1);
				data.callback(event);
				break;
			};
			}
		});

		glfwSetMouseButtonCallback(window, [](GLFWwindow* lambdaWindow, int lambdaBtn, int lambdaAction, int lambdaModifiers) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(lambdaWindow);
			switch (lambdaAction) {
			case GLFW_PRESS: {
				MouseButtonPressedEvent event(lambdaBtn);
				data.callback(event);
				break;
			}
			case GLFW_RELEASE: {
				MouseButtonReleasedEvent event(lambdaBtn);
				data.callback(event);
				break;
			}
			}
		});

		glfwSetScrollCallback(window, [](GLFWwindow* lambdaWindow, double xOffset, double yOffset) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(lambdaWindow);
			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data.callback(event);
		});

		glfwSetCursorPosCallback(window, [](GLFWwindow* lambdaWindow, double x, double y) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(lambdaWindow);
			MouseMovedEvent event((float)x, (float)y);
			data.callback(event);
		});
	}

	void WindowsWindow::Shutdown() {
		OE_CORE_INFO("App window shutting down...");
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
}