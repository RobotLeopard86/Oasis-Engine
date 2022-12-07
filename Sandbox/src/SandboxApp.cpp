#include "Oasis.h"

class Sandbox : public Oasis::Application {
public:
	Sandbox() {

	}
	
	~Sandbox() {

	}
};

Oasis::Application* Oasis::CreateApplication() {
	return new Sandbox();
}