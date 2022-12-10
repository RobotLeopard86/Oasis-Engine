#include "OasisPCH.h"
#include "LayerStack.h"

namespace Oasis {
	LayerStack::LayerStack() {
		insert = layers.begin();
	}

	LayerStack::~LayerStack() {
		for (Layer* layer : layers) {
			delete layer;
		}
	}

	void LayerStack::PutLayer(Layer* layer) {
		insert = layers.emplace(insert, layer);
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