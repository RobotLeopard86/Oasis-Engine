#include "OasisPCH.h"
#include "Log.h"
#include "Application.h"
#include "Events/ApplicationEvent.h"

namespace Oasis {
	Application::Application() {

	}
	Application::~Application() {

	}
	void Application::Run() {
		WindowResizeEvent wre(1280, 720);
		if(wre.IsInCategory(EventCategoryApplication)) {
			OASISCORE_TRACE(wre);
		}
		if (wre.IsInCategory(EventCategoryInput)) {
			OASISCORE_TRACE(wre);
		}
		while(true) {

		}
	}
}