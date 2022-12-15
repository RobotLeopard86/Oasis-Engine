#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace Oasis {
	class OASIS_API Layer {
	public:
		Layer(const std::string& name = "New Layer");
		virtual ~Layer();

		virtual void OnInit() {};
		virtual void OnShutdown() {};
		virtual void OnUpdate() {};
		virtual void OnImGuiDraw() {};

		virtual void HandleEvent(Event& event) {};
		inline const std::string& GetName() const {
			return debugName;
		}
	protected:
		std::string debugName;
	};
}