#include "OasisPCH.h"
#include "LayerStack.h"

namespace Oasis {
	LayerStack::LayerStack() {}

	LayerStack::~LayerStack() {
		for (Layer* layer : layers) {
			delete layer;
		}
	}

	void LayerStack::PutLayer(Layer* layer) {
		layers.emplace(layers.begin() + insert, layer);
		insert++;
	}

	void LayerStack::PutOverlayLayer(Layer* overlay) {
		layers.emplace_back(overlay);
	}

	void LayerStack::TakeLayer(Layer* target) {
		auto it = std::find(layers.begin(), layers.end(), target);
		if (it != layers.end()) {
			layers.erase(it);
			insert--;
		}
	}

	void LayerStack::TakeOverlayLayer(Layer* target) {
		auto it = std::find(layers.begin(), layers.end(), target);
		if (it != layers.end()) {
			layers.erase(it);
		}
	}
}