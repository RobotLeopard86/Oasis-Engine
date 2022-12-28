#include "OasisPCH.h"
#include "Log.h"
#include "Application.h"
#include "Input.h"
#include "Keycodes.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Oasis {

	Application* Application::instance = nullptr;

	static GLenum ShaderDataTypeToGLBaseType(ShaderDataType type) {
		switch(type) {
		case ShaderDataType::Float: return GL_FLOAT;
		case ShaderDataType::Float2: return GL_FLOAT;
		case ShaderDataType::Float3: return GL_FLOAT;
		case ShaderDataType::Float4: return GL_FLOAT;
		case ShaderDataType::Int: return GL_INT;
		case ShaderDataType::Int2: return GL_INT;
		case ShaderDataType::Int3: return GL_INT;
		case ShaderDataType::Int4: return GL_INT;
		case ShaderDataType::Mat3: return GL_FLOAT;
		case ShaderDataType::Mat4: return GL_FLOAT;
		case ShaderDataType::Boolean: return GL_BOOL;
		}

		OE_COREASSERT(false, "Can't convert unrecognized shader data type to OpenGL base type!");
		return 0;
	}

	Application::Application() {
		OE_COREASSERT(!instance, "Application instance already exists!");
		instance = this;

		window = std::unique_ptr<Window>(Window::NewWindow());
		window->SetEventCallback(BIND_EVENTFN(Application::HandleEvent));

		imguiLayer = new ImGuiLayer();
		PutOverlayLayer(imguiLayer);

		glGenVertexArrays(1, &vertexArray);
		glBindVertexArray(vertexArray);

		float vertices[3 * 7]{
			-0.5f, -0.5f, 0.0f, 0.0f, 0.796875f, 0.0f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.1015625f, 0.63671875f, 1.0f, 1.0f,
			0.0f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f
		};

		vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		vertexBuffer->Bind();
		{
			BufferLayout layout = {
				{ ShaderDataType::Float3, "pos" },
				{ ShaderDataType::Float4, "color" }
			};

			vertexBuffer->SetLayout(layout);
		}

		uint32_t idx = 0;
		for(const auto& elem : vertexBuffer->GetLayout().GetBufferElements()) {
			glEnableVertexAttribArray(idx);
			glVertexAttribPointer(idx, elem.GetComponentCount(), ShaderDataTypeToGLBaseType(elem.type), elem.normalized ? GL_TRUE : GL_FALSE, vertexBuffer->GetLayout().GetStride(), (const void*)elem.offset);
			idx++;
		}
		
		uint32_t indices[3]{
			0, 1, 2
		};

		indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		indexBuffer->Bind();

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