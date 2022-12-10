#include "OasisPCH.h"
#include "Log.h"
#include "Application.h"

#include <GLFW/glfw3.h>

namespace Oasis {

	#define BIND_EVENTFN(f) std::bind(&f, this, std::placeholders::_1)

	Application::Application() {
		window = std::unique_ptr<Window>(Window::NewWindow());
		window->SetEventCallback(BIND_EVENTFN(Application::HandleEvent));
	}
	Application::~Application() {

	}
	void Application::Run() {
		while(applicationRunning) {
			glClearColor(0.671875, 0, 0.8984375, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			window->OnUpdate();
		}
	}
	void Application::HandleEvent(Event& event) {
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENTFN(Application::OnWindowClose));

		OASISCORE_TRACE("An event just occurred: {0}", event);
	}
	bool Application::OnWindowClose(WindowCloseEvent& wce) {
		applicationRunning = false;
		return true;
	}
}