#pragma once

#include "Core.h"
#include "Window.h"
#include "LayerStack.h"
#include "Events/ApplicationEvent.h"
#include "ImGui/ImGuiLayer.h"

namespace Oasis {

	class OASIS_API Application {
	public:

		Application();
		virtual ~Application();

		void Run();
		void HandleEvent(Event& event);

		void PutLayer(Layer* layer);
		void PutOverlayLayer(Layer* overlay);

		inline Window& GetWindow() {
			return *window;
		}

		inline static Application& Get() {
			return *instance;
		}
	private:
		std::unique_ptr<Window> window;
		ImGuiLayer* imguiLayer;
		bool applicationRunning = true;
		LayerStack layerStack;

		static Application* instance;

		bool OnWindowClose(WindowCloseEvent& wce);
	};

	//Client must implement
	Application* CreateApplication();
}