#pragma once

namespace Oasis {
	class PlatformFunctions {
	public:
		inline static float GetElapsedTime() {
			return instance->GetElapsedTime_Impl();
		}
	protected:
		virtual float GetElapsedTime_Impl() = 0;
	private:
		static PlatformFunctions* instance;
	};
}