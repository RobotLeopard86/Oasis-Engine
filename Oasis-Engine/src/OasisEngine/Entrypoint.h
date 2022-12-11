#pragma once

#include "Log.h"

#ifdef OE_PLATFORM_WIN
	extern Oasis::Application* Oasis::CreateApplication();

	int main(int argc, char** argv) {
		Oasis::Log::Init();
		OE_CORE_INFO("Welcome to Oasis Engine!");
		OE_CORE_INFO("Creating application...");
		Oasis::Application* app = Oasis::CreateApplication();
		app->Run();
		OE_CORE_INFO("Oasis Engine shutting down...");
		delete app;
	}
#else
	#error Oasis Engine currently only supports Windows. Support for other operating systems may come in the future.
#endif