#pragma once

#include "Core.h"
#include "Events/Event.h"

#include <GLFW/glfw3.h>

namespace Oasis {
	struct WindowProperties {
		std::string title;
		unsigned int width;
		unsigned int height;

		WindowProperties(std::string title = "Oasis Engine App", unsigned int width = 1280, unsigned int height = 720)
			:
			title(title), width(width), height(height)
		{}
	};

	class OASIS_API Window {
	public:
		using CallbackFunc = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWindowWidth() const = 0;
		virtual unsigned int GetWindowHeight() const = 0;

		virtual void SetEventCallback(const CallbackFunc& callback) = 0;
		virtual void SetVSyncEnabled(bool enabled) = 0;
		virtual bool IsVSyncEnabled() const = 0;

		static Window* NewWindow(const WindowProperties& props = WindowProperties());
	};
}