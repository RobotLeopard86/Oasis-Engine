#pragma once

#include "Log.h"

#ifdef OASIS_WIN
	extern Oasis::Application* Oasis::CreateApplication();

	int main(int argc, char** argv) {
		Oasis::Log::Init();
		OASISCORE_INFO("Oasis Engine starting...");
		OASISCLIENT_INFO("Creating application...");
		Oasis::Application* app = Oasis::CreateApplication();
		OASISCORE_INFO("Oasis Engine application created. Starting app...");
		app->Run();
		OASISCORE_INFO("Oasis Engine shutting down...");
		delete app;
	}
#else
	#error Oasis Engine currently only supports Windows. Support for other operating systems may come in the future.
#endif