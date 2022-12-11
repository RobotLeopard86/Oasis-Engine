#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Oasis {
	class OASIS_API Log {
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() {
			return coreLogger;
		}
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() {
			return clientLogger;
		}
	private:
		static std::shared_ptr<spdlog::logger> coreLogger;
		static std::shared_ptr<spdlog::logger> clientLogger;
	};
}

//Logging macros
#ifdef OE_DEBUG
	#define OE_CORE_FATALERROR(...) ::Oasis::Log::GetCoreLogger()->critical(__VA_ARGS__)
	#define OE_CLIENT_FATALERROR(...) ::Oasis::Log::GetClientLogger()->critical(__VA_ARGS__)
	#define OE_CORE_ERROR(...) ::Oasis::Log::GetCoreLogger()->error(__VA_ARGS__)
	#define OE_CLIENT_ERROR(...) ::Oasis::Log::GetClientLogger()->error(__VA_ARGS__)
	#define OE_CORE_WARN(...) ::Oasis::Log::GetCoreLogger()->warn(__VA_ARGS__)
	#define OE_CLIENT_WARN(...) ::Oasis::Log::GetClientLogger()->warn(__VA_ARGS__)
	#define OE_CORE_INFO(...) ::Oasis::Log::GetCoreLogger()->info(__VA_ARGS__)
	#define OE_CLIENT_INFO(...) ::Oasis::Log::GetClientLogger()->info(__VA_ARGS__)
	#define OE_CORE_TRACE(...) ::Oasis::Log::GetCoreLogger()->trace(__VA_ARGS__)
	#define OE_CLIENT_TRACE(...) ::Oasis::Log::GetClientLogger()->trace(__VA_ARGS__)
#else
	#define OE_CORE_FATALERROR
	#define OE_CLIENT_FATALERROR
	#define OE_CORE_ERROR
	#define OE_CLIENT_ERROR
	#define OE_CORE_WARN
	#define OE_CLIENT_WARN
	#define OE_CORE_INFO
	#define OE_CLIENT_INFO
	#define OE_CORE_TRACE
	#define OE_CLIENT_TRACE
#endif