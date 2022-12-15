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

		void OnInit() override;
		void OnShutdown() override;
		void OnImGuiDraw() override;

		void Begin();
		void End();
	private:
		float time = 0.0f;
		bool succesfulImGuiInit = false;
	};
}