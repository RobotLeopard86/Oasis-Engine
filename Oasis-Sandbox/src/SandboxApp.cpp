#include "Oasis.h"
#include "glm/glm.hpp"

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/scalar_constants.hpp>

glm::mat4 camera(float Translate, glm::vec2 const& Rotate)
{
	glm::mat4 Projection = glm::perspective(glm::pi<float>() * 0.25f, 4.0f / 3.0f, 0.1f, 100.f);
	glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Translate));
	View = glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
	View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
	return Projection * View * Model;
}

class ExampleLayer : public Oasis::Layer {
public:
	ExampleLayer()
		: Layer("Example Layer") {
		auto cam = camera(5.0f, { 0.5f, 0.5f });
	}

	void OnUpdate() override {
		if(Oasis::Input::IsKeyPressed(OE_KEY_TAB)) {
			OE_CLIENT_TRACE("You pressed the tab key!");
		}
	}

	void HandleEvent(Oasis::Event& event) override {}
};

class Sandbox : public Oasis::Application {
public:
	Sandbox() {
		PutLayer(new ExampleLayer());
	}
	
	~Sandbox() {

	}
};

Oasis::Application* Oasis::CreateApplication() {
	return new Sandbox();
}