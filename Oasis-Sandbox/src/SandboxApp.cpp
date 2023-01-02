#include "Oasis.h"

class ExampleLayer : public Oasis::Layer {
public:
	ExampleLayer()
		: Layer("Sandbox"), cam(-1.6f, 1.6f, -0.9f, 0.9f), camPosition(0.0f), camRotation(0.0f), camSpeed(0.05f), camRotSpeed(2.0f) {}

	void OnUpdate() override {
		if(Oasis::Input::IsKeyPressed(OE_KEY_W)) {
			camPosition.y -= camSpeed;
		} else if(Oasis::Input::IsKeyPressed(OE_KEY_S)) {
			camPosition.y += camSpeed;
		}
		
		if(Oasis::Input::IsKeyPressed(OE_KEY_A)) {
			camPosition.x -= camSpeed;
		} else if(Oasis::Input::IsKeyPressed(OE_KEY_D)) {
			camPosition.x += camSpeed;
		}
		
		if (Oasis::Input::IsKeyPressed(OE_KEY_R)) {
			camPosition = glm::vec3(0.0f);
			camRotation = 0.0f;
		}

		if (Oasis::Input::IsKeyPressed(OE_KEY_E)) {
			camRotation -= camRotSpeed;
			if(camRotation < 1) camRotation = 360;
		}
		else if (Oasis::Input::IsKeyPressed(OE_KEY_Q)) {
			camRotation += camRotSpeed;
			if(camRotation > 359) camRotation = 0;
		}

		cam.SetPosition(camPosition);
		cam.SetRotation(camRotation);

		Oasis::Renderer::StartScene(cam);
		Oasis::Renderer::SubmitRawGeometry(vertexArray, shader);
		Oasis::Renderer::ConcludeScene();
	}

	void OnImGuiDraw() override {
		ImGui::Begin("Controls");
		ImGui::Text("WASD to move, E and Q to rotate, R to reset");
		ImGui::End();
	}

	void OnInit() override {
		vertexArray.reset(Oasis::VertexArray::Create());

		float vertices[6 * 7]{
			0.4375f, 0.75f, 0.0f, 0.8984375f, 0.0f, 0.0f, 1.0f,
			-0.4375f, 0.75f, 0.0f, 0.99609375f, 0.45703125f, 0.1015625f, 1.0f,
			-0.85f, 0.0f, 0.0f, 0.99609375f, 0.796875f, 0.0f, 1.0f,
			0.85f, 0.0f, 0.0f, 0.671875f, 0.0f, 0.8984375f, 1.0f,
			0.4375f, -0.75f, 0.0f, 0.0f, 0.44921875f, 0.8984375f, 1.0f,
			-0.4375f, -0.75f, 0.0f, 0.19921875f, 0.796875f, 0.19921875f, 1.0f
		};

		vertexBuffer.reset(Oasis::VertexBuffer::Create(vertices, sizeof(vertices)));

		Oasis::BufferLayout layout = {
			{ Oasis::ShaderDataType::Float3, "pos" },
			{ Oasis::ShaderDataType::Float4, "color" }
		};

		vertexBuffer->SetLayout(layout);

		vertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[4 * 3]{
			0, 3, 4,
			1, 2, 5,
			0, 1, 5,
			0, 4, 5
		};

		indexBuffer.reset(Oasis::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		vertexArray->SetIndexBuffer(indexBuffer);

		std::string vertexSrc = R"(
			#version 330 core

			layout(location=0) in vec3 pos;
			layout(location=1) in vec4 color;

			uniform mat4 vpm;

			out vec4 vertexColor;

			void main() {
				vertexColor = color;
				gl_Position = vpm * vec4(pos, 1.0);
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

		shader.reset(new Oasis::Shader(vertexSrc, fragmentSrc));

		Oasis::RenderJob::SetClearColor({ 0.15, 0.15, 0.15, 1.0 });
	}

	void HandleEvent(Oasis::Event& event) override {}
private:
	std::shared_ptr<Oasis::VertexArray> vertexArray;
	std::shared_ptr<Oasis::VertexBuffer> vertexBuffer;
	std::shared_ptr<Oasis::IndexBuffer> indexBuffer;
	std::shared_ptr<Oasis::Shader> shader;

	Oasis::OrthographicCamera cam;
	glm::vec3 camPosition;
	float camRotation;
	float camSpeed;
	float camRotSpeed;
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