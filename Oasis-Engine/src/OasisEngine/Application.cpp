#include "OasisPCH.h"
#include "Log.h"
#include "Application.h"
#include "Input.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Oasis {

	Application* Application::instance = nullptr;

	Application::Application() {
		COREASSERT(!instance, "Application instance already exists!");
		instance = this;

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

			auto [x, y] = Input::GetMousePos();
			OASISCORE_TRACE("Mouse position: {0}, {1}", x, y);

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
		layer->OnInit();
		layerStack.PutLayer(layer);
	}
	void Application::PutOverlayLayer(Layer* overlay) {
		overlay->OnInit();
		layerStack.PutOverlayLayer(overlay);
	}
}