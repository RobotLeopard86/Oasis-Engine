#pragma once

#include "OasisEngine/Layer.h"

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
	};
}