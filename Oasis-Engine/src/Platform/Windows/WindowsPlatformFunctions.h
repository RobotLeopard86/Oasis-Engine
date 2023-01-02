#pragma once

#include "OasisEngine/PlatformFunctions.h"

namespace Oasis {
	class WindowsPlatformFunctions : public PlatformFunctions {
	protected:
		float GetElapsedTime_Impl() override;
	};
}