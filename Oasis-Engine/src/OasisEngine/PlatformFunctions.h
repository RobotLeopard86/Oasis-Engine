#pragma once

namespace Oasis {
	class PlatformFunctions {
	public:
		inline static float GetFrameTime() {
			return instance->GetFrameTime_Impl();
		}
	protected:
		virtual float GetFrameTime_Impl() = 0;
	private:
		static PlatformFunctions* instance;
	};
}