#include "OasisPCH.h"
#include "Layer.h"

namespace Oasis {

	Layer::Layer(const std::string& debugName)
		: debugName(debugName) {}

	Layer::~Layer() {}

	void Layer::OnInit() {}
	void Layer::OnShutdown() {}
	void Layer::OnUpdate() {}
	void Layer::HandleEvent(Event& event) {}
}