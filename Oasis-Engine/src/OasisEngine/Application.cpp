#include "OasisPCH.h"
#include "Log.h"
#include "Application.h"
#include "Input.h"
#include "Keycodes.h"

namespace Oasis {

	Application* Application::instance = nullptr;

	Application::Application() {
		OE_COREASSERT(!instance, "Application instance already exists!");
		instance = this;

		window = std::unique_ptr<Window>(Window::NewWindow());
		window->SetEventCallback(BIND_EVENTFN(Application::HandleEvent));

		imguiLayer = new ImGuiLayer();
		PutOverlayLayer(imguiLayer);
	}
	Application::~Application() {}

	void Application::Run() {
		while(applicationRunning) {
			for(Layer* layer : layerStack) {
				layer->OnUpdate();
			}

			imguiLayer->Begin();
			for (Layer* layer : layerStack) {
				layer->OnImGuiDraw();
			}
			imguiLayer->End();

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