#pragma once

#include "Core.h"
#include "Window.h"

namespace Oasis {
	class OASIS_API Application {
	public:
		Application();
		virtual ~Application();

		void Run();
	private:
		std::unique_ptr<Window> window;
		bool applicationRunning = true;
	};

	//Client must implement
	Application* CreateApplication();
}