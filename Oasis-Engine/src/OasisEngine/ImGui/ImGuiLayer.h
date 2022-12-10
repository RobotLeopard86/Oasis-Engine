#pragma once

#include "OasisEngine/Layer.h"
#include "OasisEngine/Events/KeyEvent.h"
#include "OasisEngine/Events/MouseEvent.h"
#include "OasisEngine/Events/ApplicationEvent.h"

namespace Oasis {
	class OASIS_API ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnInit();
		void OnShutdown();
		void OnUpdate();
		void HandleEvent(Event& event);
	private:
		float time = 0.0f;

		bool OnMousePressed(MouseButtonPressedEvent& event);
		bool OnMouseReleased(MouseButtonReleasedEvent& event);
		bool OnMouseMoved(MouseMovedEvent& event);
		bool OnMouseScrolled(MouseScrolledEvent& event);
		bool OnKeyPressed(KeyPressedEvent& event);
		bool OnKeyTyped(KeyTypedEvent& event);
		bool OnKeyReleased(KeyReleasedEvent& event);
		bool OnWindowResized(WindowResizeEvent& event);
	};
}