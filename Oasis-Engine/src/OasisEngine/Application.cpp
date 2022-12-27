#include "OasisPCH.h"
#include "Log.h"
#include "Application.h"
#include "Input.h"
#include "Keycodes.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Oasis {

	Application* Application::instance = nullptr;

	Application::Application() {
		OE_COREASSERT(!instance, "Application instance already exists!");
		instance = this;

		window = std::unique_ptr<Window>(Window::NewWindow());
		window->SetEventCallback(BIND_EVENTFN(Application::HandleEvent));

		imguiLayer = new ImGuiLayer();
		PutOverlayLayer(imguiLayer);

		glGenVertexArrays(1, &vertexArray);
		glBindVertexArray(vertexArray);

		glGenBuffers(1, &vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

		float vertices[3 * 3]{
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		glGenBuffers(1, &indexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
		
		unsigned int indices[3]{
			0, 1, 2
		};

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	}
	Application::~Application() {}

	void Application::Run() {
		while(applicationRunning) {
			glClearColor(0, 0.3984375, 0.796875, 0.5);
			glClear(GL_COLOR_BUFFER_BIT);

			glBindVertexArray(vertexArray);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

			for(Layer* layer : layerStack) {
				layer->OnUpdate();
			}

			imguiLayer->Begin();
			for (Layer* layer : layerStack) {
				layer->OnImGuiDraw();
			}
			imguiLayer->End();

			window->OnUpdate();
		}
	}
	void Application::HandleEvent(Event& event) {
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENTFN(Application::OnWindowClose));

		for (auto it = layerStack.end(); it != layerStack.begin();) {
			(*--it)->HandleEvent(event);
			if(event.handled) {
				break;
			}
		}
	}
	bool Application::OnWindowClose(WindowCloseEvent& wce) {
		applicationRunning = false;
		return true;
	}
	void Application::PutLayer(Layer* layer) {
		layer->OnInit();
		layerStack.PutLayer(layer);
	}
	void Application::PutOverlayLayer(Layer* overlay) {
		overlay->OnInit();
		layerStack.PutOverlayLayer(overlay);
	}
}