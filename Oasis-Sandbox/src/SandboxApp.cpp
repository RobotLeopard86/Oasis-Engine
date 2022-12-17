#include "Oasis.h"
#include "imgui/imgui.h"

class ExampleLayer : public Oasis::Layer {
public:
	ExampleLayer()
		: Layer("Example") {}

	void OnUpdate() override {
		if (Oasis::Input::IsKeyPressed(OE_KEY_TAB)) {
			OE_CLIENT_TRACE("You pressed the tab key!");
		}
	}

	void OnImGuiDraw() override {
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
	}

	void HandleEvent(Oasis::Event& event) override {}

};

class Sandbox : public Oasis::Application
{
public:
	Sandbox() {
		PutLayer(new ExampleLayer());
	}

	~Sandbox() {}

};

Oasis::Application* Oasis::CreateApplication() {
	return new Sandbox();
}