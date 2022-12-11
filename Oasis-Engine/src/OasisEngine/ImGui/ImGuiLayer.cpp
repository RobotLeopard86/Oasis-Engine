#include "OasisPCH.h"
#include "ImGuiLayer.h"
#include "ImGuiCustomStyle.h"

#include "imgui.h"
#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"
#include "OasisEngine/Application.h"

//TEMPORARY
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Oasis {

	ImGuiLayer::ImGuiLayer()
		: Layer("ImGui Layer") {}

	ImGuiLayer::~ImGuiLayer() {}

	void ImGuiLayer::OnInit() {
		ImGui::CreateContext();
		ImGuiStyleOasis();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

		//Temporary, should eventually be migrated to Oasis Engine key codes
		io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
		io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
		io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
		io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
		io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
		io.KeyMap[ImGuiKey_B] = GLFW_KEY_B;
		io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
		io.KeyMap[ImGuiKey_D] = GLFW_KEY_D;
		io.KeyMap[ImGuiKey_E] = GLFW_KEY_E;
		io.KeyMap[ImGuiKey_F] = GLFW_KEY_F;
		io.KeyMap[ImGuiKey_G] = GLFW_KEY_G;
		io.KeyMap[ImGuiKey_H] = GLFW_KEY_H;
		io.KeyMap[ImGuiKey_I] = GLFW_KEY_I;
		io.KeyMap[ImGuiKey_J] = GLFW_KEY_J;
		io.KeyMap[ImGuiKey_K] = GLFW_KEY_K;
		io.KeyMap[ImGuiKey_L] = GLFW_KEY_L;
		io.KeyMap[ImGuiKey_M] = GLFW_KEY_M;
		io.KeyMap[ImGuiKey_N] = GLFW_KEY_N;
		io.KeyMap[ImGuiKey_O] = GLFW_KEY_O;
		io.KeyMap[ImGuiKey_P] = GLFW_KEY_P;
		io.KeyMap[ImGuiKey_Q] = GLFW_KEY_Q;
		io.KeyMap[ImGuiKey_R] = GLFW_KEY_R;
		io.KeyMap[ImGuiKey_S] = GLFW_KEY_S;
		io.KeyMap[ImGuiKey_T] = GLFW_KEY_T;
		io.KeyMap[ImGuiKey_U] = GLFW_KEY_U;
		io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
		io.KeyMap[ImGuiKey_W] = GLFW_KEY_W;
		io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
		io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
		io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

		int imguiInit = ImGui_ImplOpenGL3_Init("#version 410");
		OE_COREASSERT(imguiInit, "ImGui refused to initialize!");
	}

	void ImGuiLayer::OnShutdown() {}

	void ImGuiLayer::OnUpdate() {
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2(app.GetWindow().GetWindowWidth(), app.GetWindow().GetWindowHeight());

		float glfwTime = (float)glfwGetTime();
		io.DeltaTime = glfwTime > 0.0f ? (glfwTime - time) : (1.0f / 60.0f);
		time = glfwTime;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::HandleEvent(Event& event) {
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENTFN(ImGuiLayer::OnKeyPressed));
		dispatcher.Dispatch<KeyTypedEvent>(BIND_EVENTFN(ImGuiLayer::OnKeyTyped));
		dispatcher.Dispatch<KeyReleasedEvent>(BIND_EVENTFN(ImGuiLayer::OnKeyReleased));
		dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_EVENTFN(ImGuiLayer::OnMousePressed));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(BIND_EVENTFN(ImGuiLayer::OnMouseReleased));
		dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENTFN(ImGuiLayer::OnMouseMoved));
		dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENTFN(ImGuiLayer::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENTFN(ImGuiLayer::OnWindowResized));
	}

	bool ImGuiLayer::OnKeyPressed(KeyPressedEvent& event) {
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[event.GetKeyCode()] = true;

		return false;
	}
	bool ImGuiLayer::OnKeyReleased(KeyReleasedEvent& event) {
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[event.GetKeyCode()] = false;

		io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
		io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
		io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
		io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];

		return false;
	}
	bool ImGuiLayer::OnKeyTyped(KeyTypedEvent& event) {
		ImGuiIO& io = ImGui::GetIO();

		unsigned int keycode = event.GetKeyCode();
		if (keycode > 0 && keycode < 0x10000) {
			io.AddInputCharacter((unsigned short)keycode);
		}

		return false;
	}
	bool ImGuiLayer::OnMousePressed(MouseButtonPressedEvent& event) {
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[event.GetMouseButton()] = true;

		return false;
	}
	bool ImGuiLayer::OnMouseReleased(MouseButtonReleasedEvent& event) {
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[event.GetMouseButton()] = false;

		return false;
	}
	bool ImGuiLayer::OnMouseMoved(MouseMovedEvent& event) {
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(event.GetX(), event.GetY());

		return false;
	}
	bool ImGuiLayer::OnMouseScrolled(MouseScrolledEvent& event) {
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheel += event.GetYOffset();
		io.MouseWheelH += event.GetXOffset();

		return false;
	}
	bool ImGuiLayer::OnWindowResized(WindowResizeEvent& event) {
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(event.GetWidth(), event.GetHeight());
		io.DisplayFramebufferScale = ImVec2(1, 1);
		glViewport(0, 0, event.GetWidth(), event.GetHeight());
		
		return false;
	}

}