#pragma once

#ifdef OASIS_WIN
	#ifdef OASISDLL
		#define OASIS_API __declspec(dllexport)
	#else
		#define OASIS_API __declspec(dllimport)
	#endif
#else
	#error Oasis Engine currently only supports Windows. Support for other operating systems may come in the future.
#endif

#ifdef OASIS_ALLOWASSERTS
	#define ASSERT(x, ...) { if(!(x)) { OASISCLIENT_ERROR("FAILED ASSERTION ON CLIENT: {0}", __VA_ARGS__); __debugbreak(); } }
	#define COREASSERT(x, ...) { if(!(x)) { OASISCORE_ERROR("FAILED ASSERTION ON CLIENT: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define ASSERT(x, ...)
	#define COREASSERT(x, ...)
#endif

#define BIT(x) (1 << x)
#define BIND_EVENTFN(f) std::bind(&f, this, std::placeholders::_1)