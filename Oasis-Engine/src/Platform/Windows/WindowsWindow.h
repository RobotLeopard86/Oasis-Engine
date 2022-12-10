#pragma once

#include "OasisEngine/Window.h"

#include <GLFW/glfw3.h>

namespace Oasis {
	class WindowsWindow : public Window {
	public:
		WindowsWindow(const WindowProperties& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWindowWidth() const override { 
			return windowData.width; 
		}

		inline unsigned int GetWindowHeight() const override { 
			return windowData.height; 
		}

		inline void SetEventCallback(const CallbackFunc& callback) override {
			windowData.callback = callback; 
		}

		void SetVSyncEnabled(bool enabled) override;
		bool IsVSyncEnabled() const override;
	private:
		virtual void Init(const WindowProperties& props);
		virtual void Shutdown();

		GLFWwindow* window;

		struct WindowData {
			std::string title;
			unsigned int width, height;
			bool useVSync;

			CallbackFunc callback;
		};

		WindowData windowData;
	};
}