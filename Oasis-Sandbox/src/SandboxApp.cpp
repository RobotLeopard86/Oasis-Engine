#include "Oasis.h"

class ExampleLayer : public Oasis::Layer {
public:
	ExampleLayer()
		: Layer("Example Layer") {}

	void OnUpdate() override {
		if(Oasis::Input::IsKeyPressed(OE_KEY_TAB)) {
			OE_CORE_TRACE("You pressed the tab key!");
		}
	}

	void HandleEvent(Oasis::Event& event) override {}
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