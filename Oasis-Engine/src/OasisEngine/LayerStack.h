#pragma once

#include "Core.h"
#include "Layer.h"

#include <vector>

namespace Oasis {
	class OASIS_API LayerStack {
	public:
		LayerStack();
		~LayerStack();

		void PutLayer(Layer* layer);
		void PutOverlayLayer(Layer* overlay);
		void TakeLayer(Layer* target);
		void TakeOverlayLayer(Layer* target);

		std::vector<Layer*>::iterator begin() {
			return layers.begin();
		}
		std::vector<Layer*>::iterator end() {
			return layers.end();
		}
	private:
		std::vector<Layer*> layers;
		std::vector<Layer*>::iterator insert;
	};
}