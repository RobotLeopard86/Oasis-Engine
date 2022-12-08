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

#define BIT(x) (1 << x)