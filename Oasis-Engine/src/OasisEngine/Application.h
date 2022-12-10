#pragma once

#include "Core.h"
#include "Window.h"
#include "Events/ApplicationEvent.h"

namespace Oasis {
	class OASIS_API Application {
	public:
		Application();
		virtual ~Application();

		void Run();
		void HandleEvent(Event& event);
	private:
		std::unique_ptr<Window> window;
		bool applicationRunning = true;

		bool OnWindowClose(WindowCloseEvent& wce);
	};

	//Client must implement
	Application* CreateApplication();
}