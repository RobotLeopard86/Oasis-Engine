#include "Oasis.h"

class ExampleLayer : public Oasis::Layer {
public:
	ExampleLayer()
		: Layer("Sandbox"), cam(90.0f, 1000.0f), camPosition(0.0f), camRotation(0.0f), camSpeed(1.0f),
		camRotSpeed(2.0f), lastSecondTime(0.0f), fps(0.0f), frameCount(0), lastDeltaSeconds(0.0f) {}

	void OnUpdate(Oasis::Timestep step) override {
		if(Oasis::Input::IsKeyPressed(OE_KEY_W)) {
			camPosition.y -= camSpeed * step;
		} else if(Oasis::Input::IsKeyPressed(OE_KEY_S)) {
			camPosition.y += camSpeed * step;
		}
		
		if(Oasis::Input::IsKeyPressed(OE_KEY_A)) {
			camPosition.x -= camSpeed * step;
		} else if(Oasis::Input::IsKeyPressed(OE_KEY_D)) {
			camPosition.x += camSpeed * step;
		}
		
		if(Oasis::Input::IsKeyPressed(OE_KEY_R)) {
			camPosition = glm::vec3(0.0f);
			camRotation = glm::vec3(0.0f);
		} else if(Oasis::Input::IsKeyPressed(OE_KEY_Z)) {
			camRotation = glm::vec3(0.0f);
		} else if(Oasis::Input::IsKeyPressed(OE_KEY_C)) {
			camPosition = glm::vec3(0.0f);
		}

		if(Oasis::Input::IsKeyPressed(OE_KEY_E)) {
			camRotation.x -= camRotSpeed;
			if(camRotation.x < 1) camRotation.x = 360;
		}
		else if(Oasis::Input::IsKeyPressed(OE_KEY_Q)) {
			camRotation.x += camRotSpeed;
			if(camRotation.x > 359) camRotation.x = 0;
		}

		if (Oasis::Input::IsKeyPressed(OE_KEY_Z)) {
			camRotation.y -= camRotSpeed;
			if (camRotation.y < 1) camRotation.y = 360;
		}
		else if (Oasis::Input::IsKeyPressed(OE_KEY_X)) {
			camRotation.y += camRotSpeed;
			if (camRotation.y > 359) camRotation.y = 0;
		}

		if (Oasis::Input::IsKeyPressed(OE_KEY_B)) {
			camRotation.z -= camRotSpeed;
			if (camRotation.z < 1) camRotation.z = 360;
		}
		else if (Oasis::Input::IsKeyPressed(OE_KEY_N)) {
			camRotation.z += camRotSpeed;
			if (camRotation.z > 359) camRotation.z = 0;
		}

		cam.SetPosition(camPosition);
		cam.SetRotation(camRotation);

		Oasis::Renderer::StartScene(cam);
		Oasis::Renderer::SubmitRawGeometry(vertexArray, shader);
		Oasis::Renderer::ConcludeScene();
	}

	void OnImGuiDraw(Oasis::Timestep step) override {
		frameCount++;

		ImGui::Begin("Controls");
		ImGui::Text("WASD to move,\nE and Q to rotate X axis,\nZ and X to rotate Y axis,\nB and N to rotate Z axis,\nR to reset everything,\nC to reset position,\nZ to reset rotation");
		ImGui::End();

		float elapsed = Oasis::PlatformFunctions::GetElapsedTime();
		
		if(elapsed >= lastSecondTime + 1.0f) {
			fps = frameCount;
			frameCount = 0;
			lastSecondTime = elapsed;
			lastDeltaSeconds = step.GetSeconds();
		}

		std::stringstream ss;
		ss << "Delta time (seconds): " << lastDeltaSeconds << "\nDelta time (milliseconds): " << lastDeltaSeconds * 1000 << "\nFPS: " << fps << "\nVSync Enabled: " << BoolToYesNo(Oasis::Application::Get().GetWindow().IsVSyncEnabled());

		ImGui::SetNextWindowPos(ImVec2(150, 500), ImGuiCond_Once);
		ImGui::SetNextWindowSize(ImVec2(250, 150), ImGuiCond_Once);
		ImGui::Begin("Timing");
		ImGui::Text(ss.str().c_str());
		
		if(ImGui::Button("Toggle VSync Enabled")) {
			Oasis::Application::Get().GetWindow().SetVSyncEnabled(!Oasis::Application::Get().GetWindow().IsVSyncEnabled());
		}

		ImGui::End();
	}

	std::string BoolToYesNo(bool input) {
		if(input) {
			return "Yes";
		} else {
			return "No";
		}
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

	Oasis::PerspectiveCamera cam;
	glm::vec3 camPosition;
	glm::vec3 camRotation;
	float camSpeed;
	float camRotSpeed;

	float lastSecondTime;
	float lastDeltaSeconds;

	int fps;
	int frameCount;
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