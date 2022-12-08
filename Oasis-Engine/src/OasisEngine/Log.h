#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Oasis {
	class OASIS_API Log {
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() {
			return s_CoreLogger;
		}
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() {
			return s_ClientLogger;
		}
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

//Logging macros
#ifdef OASISDEV
	#define OASISCORE_FATALERROR(...) ::Oasis::Log::GetCoreLogger()->critical(__VA_ARGS__)
	#define OASISCLIENT_FATALERROR(...) ::Oasis::Log::GetClientLogger()->critical(__VA_ARGS__)
	#define OASISCORE_ERROR(...) ::Oasis::Log::GetCoreLogger()->error(__VA_ARGS__)
	#define OASISCLIENT_ERROR(...) ::Oasis::Log::GetClientLogger()->error(__VA_ARGS__)
	#define OASISCORE_WARN(...) ::Oasis::Log::GetCoreLogger()->warn(__VA_ARGS__)
	#define OASISCLIENT_WARN(...) ::Oasis::Log::GetClientLogger()->warn(__VA_ARGS__)
	#define OASISCORE_INFO(...) ::Oasis::Log::GetCoreLogger()->info(__VA_ARGS__)
	#define OASISCLIENT_INFO(...) ::Oasis::Log::GetClientLogger()->info(__VA_ARGS__)
	#define OASISCORE_TRACE(...) ::Oasis::Log::GetCoreLogger()->trace(__VA_ARGS__)
	#define OASISCLIENT_TRACE(...) ::Oasis::Log::GetClientLogger()->trace(__VA_ARGS__)
#else
	#define OASISCORE_FATALERROR
	#define OASISCLIENT_FATALERROR
	#define OASISCORE_ERROR
	#define OASISCLIENT_ERROR
	#define OASISCORE_WARN
	#define OASISCLIENT_WARN
	#define OASISCORE_INFO
	#define OASISCLIENT_INFO
	#define OASISCORE_TRACE
	#define OASISCLIENT_TRACE
#endif