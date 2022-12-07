#pragma once

#include "Core.h"

namespace Oasis {
	class OASIS_API Application {
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	//Client must implement
	Application* CreateApplication();
}