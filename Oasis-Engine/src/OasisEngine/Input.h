#pragma once

#include "Core.h"

namespace Oasis {
	class OASIS_API Input {
	public:
		inline static bool IsKeyPressed(int keycode) {
			return instance->IsKeyPressed_Impl(keycode);
		}
		inline static bool IsMouseButtonPressed(int button) {
			return instance->IsMouseButtonPressed_Impl(button);
		}
		inline static float GetMouseX() {
			return instance->GetMouseX_Impl();
		}
		inline static float GetMouseY() {
			return instance->GetMouseY_Impl();
		}
		inline static std::pair<float, float> GetMousePos() {
			return instance->GetMousePos_Impl();
		}
	protected:
		virtual bool IsKeyPressed_Impl(int keycode) = 0;
		virtual bool IsMouseButtonPressed_Impl(int button) = 0;
		virtual float GetMouseX_Impl() = 0;
		virtual float GetMouseY_Impl() = 0;
		virtual std::pair<float, float> GetMousePos_Impl() = 0;
	private:
		static Input* instance;
	};
}