#pragma once

#ifdef OE_PLATFORM_WIN
#ifdef OE_DYNAMICLNK
	#ifdef OE_DLL
		#define OASIS_API __declspec(dllexport)
	#else
		#define OASIS_API __declspec(dllimport)
#endif
#else
	#define OASIS_API
#endif
#else
	#error Oasis Engine currently only supports Windows. Support for other operating systems may come in the future.
#endif

#ifdef OE_ALLOWASSERTS
	#define OE_CLIENTASSERT(x, ...) { if(!(x)) { OE_CLIENT_ERROR("FAILED CLIENT ASSERTION: {0}", __VA_ARGS__); __debugbreak(); } }
	#define OE_COREASSERT(x, ...) { if(!(x)) { OE_CORE_ERROR("FAILED CORE ASSERTION: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define OE_CLIENTASSERT(x, ...)
	#define OE_COREASSERT(x, ...)
#endif

#define BIT(x) (1 << x)
#define BIND_EVENTFN(f) std::bind(&f, this, std::placeholders::_1)