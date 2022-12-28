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

		float vertices[3 * 3]{
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f
		};

		vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		vertexBuffer->Bind();

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
		
		uint32_t indices[3]{
			0, 1, 2
		};

		indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		indexBuffer->Bind();

		std::string vertexSrc = R"(
			#version 330 core

			layout(location=0) in vec3 pos;

			out vec3 vertexPos;

			void main() {
				vertexPos = pos;
				gl_Position = vec4(pos, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location=0) out vec4 color;

			in vec3 vertexPos;

			void main() {
				color = vec4((vertexPos + 0.15) * 2.75, 1.0);
			}
		)";

		shader.reset(new Shader(vertexSrc, fragmentSrc));
	}
	Application::~Application() {}

	void Application::Run() {
		while(applicationRunning) {
			glClearColor(0.15, 0.15, 0.15, 1.0);
			glClear(GL_COLOR_BUFFER_BIT);

			shader->Bind();
			glBindVertexArray(vertexArray);
			glDrawElements(GL_TRIANGLES, indexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

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