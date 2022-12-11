#pragma once

#include "OasisEngine/Input.h"

namespace Oasis {
	class WindowsInput : public Input {
	protected:
		bool IsKeyPressed_Impl(int keycode) override;
		bool IsMouseButtonPressed_Impl(int button) override;
		float GetMouseX_Impl() override;
		float GetMouseY_Impl() override;
		std::pair<float, float> GetMousePos_Impl() override;
	};
}