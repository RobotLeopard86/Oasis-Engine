#pragma once

#include <stdio.h>

#include "Log.h"

#ifdef OASIS_WIN
	extern Oasis::Application* Oasis::CreateApplication();

	int main(int argc, char** argv) {
		Oasis::Log::Init();
		Oasis::Application* app = Oasis::CreateApplication();
		app->Run();
		delete app;
	}
#else
	#error Oasis Engine currently only supports Windows. Support for other operating systems may come in the future.
#endif