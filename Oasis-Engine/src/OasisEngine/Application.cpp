#include "OasisPCH.h"
#include "Log.h"
#include "Application.h"
#include "Input.h"
#include "Keycodes.h"
#include "Rendering/RenderJob.h"

namespace Oasis {

	Application* Application::instance = nullptr;

	Application::Application() {
		OE_COREASSERT(!instance, "Application instance already exists!");
		instance = this;

		window = std::unique_ptr<Window>(Window::NewWindow());
		window->SetEventCallback(BIND_EVENTFN(Application::HandleEvent));

		imguiLayer = new ImGuiLayer();
		PutOverlayLayer(imguiLayer);

		vertexArray.reset(VertexArray::Create());

		float vertices[6 * 7]{
			0.25f, 0.75f, 0.0f, 0.8984375f, 0.0f, 0.0f, 1.0f,
			-0.25f, 0.75f, 0.0f, 0.99609375f, 0.45703125f, 0.1015625f, 1.0f,
			-0.5f, 0.0f, 0.0f, 0.99609375f, 0.796875f, 0.0f, 1.0f,
			0.5f, 0.0f, 0.0f, 0.671875f, 0.0f, 0.8984375f, 1.0f,
			0.25f, -0.75f, 0.0f, 0.0f, 0.44921875f, 0.8984375f, 1.0f,
			-0.25f, -0.75f, 0.0f, 0.19921875f, 0.796875f, 0.19921875f, 1.0f
		};

		vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		BufferLayout layout = {
			{ ShaderDataType::Float3, "pos" },
			{ ShaderDataType::Float4, "color" }
		};

		vertexBuffer->SetLayout(layout);

		vertexArray->AddVertexBuffer(vertexBuffer);
		
		uint32_t indices[4 * 3]{
			0, 3, 4,
			1, 2, 5,
			0, 1, 5,
			0, 4, 5
		};

		indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		vertexArray->SetIndexBuffer(indexBuffer);

		std::string vertexSrc = R"(
			#version 330 core

			layout(location=0) in vec3 pos;
			layout(location=1) in vec4 color;

			out vec4 vertexColor;

			void main() {
				vertexColor = color;
				gl_Position = vec4(pos, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location=0) out vec4 color;

			in vec4 vertexColor;

			void main() {
				color = vertexColor;
			}
		)";

		shader.reset(new Shader(vertexSrc, fragmentSrc));

		RenderJob::SetClearColor({ 0.15, 0.15, 0.15, 1.0 });
	}
	Application::~Application() {}

	void Application::Run() {
		while(applicationRunning) {
			RenderJob::ClearScreen();

			shader->Bind();
			vertexArray->Bind();
			RenderJob::DrawIndexed(vertexArray);

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