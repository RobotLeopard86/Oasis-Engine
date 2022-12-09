#include "OasisPCH.h"
#include "Log.h"
#include "Application.h"
#include "Events/ApplicationEvent.h"

#include <GLFW/glfw3.h>

namespace Oasis {
	Application::Application() {
		window = std::unique_ptr<Window>(Window::NewWindow());
	}
	Application::~Application() {

	}
	void Application::Run() {
		while(applicationRunning) {
			glClearColor(0.671875, 0, 0.8984375, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			window->OnUpdate();

			applicationRunning = !window->ShouldWindowClose();
		}
	}
}