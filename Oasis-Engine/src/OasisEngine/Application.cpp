#include "OasisPCH.h"
#include "Log.h"
#include "Application.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

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
			glClearColor(0, 0.69921875, 0.5234375, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for(Layer* layer : layerStack) {
				layer->OnUpdate();
			}

			window->OnUpdate();
		}
	}
	void Application::HandleEvent(Event& event) {
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENTFN(Application::OnWindowClose));

		for (auto it = layerStack.end(); it != layerStack.begin();) {
			(*--it)->HandleEvent(event);
			if(event.handled) {
				break;
			}
		}
	}
	bool Application::OnWindowClose(WindowCloseEvent& wce) {
		applicationRunning = false;
		return true;
	}
	void Application::PutLayer(Layer* layer) {
		layerStack.PutLayer(layer);
	}
	void Application::PutOverlayLayer(Layer* overlay) {
		layerStack.PutOverlayLayer(overlay);
	}
}