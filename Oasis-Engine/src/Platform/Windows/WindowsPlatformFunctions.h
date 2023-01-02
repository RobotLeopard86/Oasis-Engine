#pragma once

#include "OasisEngine/PlatformFunctions.h"

namespace Oasis {
	class WindowsPlatformFunctions : public PlatformFunctions {
	protected:
		float GetFrameTime_Impl() override;
	};
}