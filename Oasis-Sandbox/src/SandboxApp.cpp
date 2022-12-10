#include "Oasis.h"

class ExampleLayer : public Oasis::Layer {
public:
	ExampleLayer()
		: Layer("Example Layer") {}

	void OnUpdate() override {
		OASISCORE_INFO("Example Layer update!");
	}

	void HandleEvent(Oasis::Event& event) override {
		OASISCORE_TRACE("Example Layer received event: {0}", event);
	}
};

class Sandbox : public Oasis::Application {
public:
	Sandbox() {
		PutLayer(new ExampleLayer());
		PutOverlayLayer(new Oasis::ImGuiLayer());
	}
	
	~Sandbox() {

	}
};

Oasis::Application* Oasis::CreateApplication() {
	return new Sandbox();
}