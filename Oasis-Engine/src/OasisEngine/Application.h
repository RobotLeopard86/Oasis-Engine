#pragma once

#include "Core.h"
#include "Window.h"
#include "LayerStack.h"
#include "Events/ApplicationEvent.h"

namespace Oasis {
	class OASIS_API Application {
	public:
		Application();
		virtual ~Application();

		void Run();
		void HandleEvent(Event& event);

		void PutLayer(Layer* layer);
		void PutOverlayLayer(Layer* overlay);
	private:
		std::unique_ptr<Window> window;
		bool applicationRunning = true;
		LayerStack layerStack;

		bool OnWindowClose(WindowCloseEvent& wce);
	};

	//Client must implement
	Application* CreateApplication();
}