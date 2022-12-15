#include "OasisPCH.h"
#include "ImGuiLayer.h"
#include "ImGuiCustomStyle.h"

#include "imgui.h"
#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"
#include "OasisEngine/Application.h"

#include "OasisEngine/Keycodes.h"

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
		io.KeyMap[ImGuiKey_Tab] = OE_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = OE_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = OE_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = OE_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow] = OE_KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = OE_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown] = OE_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home] = OE_KEY_HOME;
		io.KeyMap[ImGuiKey_End] = OE_KEY_END;
		io.KeyMap[ImGuiKey_Insert] = OE_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete] = OE_KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = OE_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space] = OE_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter] = OE_KEY_ENTER;
		io.KeyMap[ImGuiKey_Escape] = OE_KEY_ESCAPE;
		io.KeyMap[ImGuiKey_A] = OE_KEY_A;
		io.KeyMap[ImGuiKey_B] = OE_KEY_B;
		io.KeyMap[ImGuiKey_C] = OE_KEY_C;
		io.KeyMap[ImGuiKey_D] = OE_KEY_D;
		io.KeyMap[ImGuiKey_E] = OE_KEY_E;
		io.KeyMap[ImGuiKey_F] = OE_KEY_F;
		io.KeyMap[ImGuiKey_G] = OE_KEY_G;
		io.KeyMap[ImGuiKey_H] = OE_KEY_H;
		io.KeyMap[ImGuiKey_I] = OE_KEY_I;
		io.KeyMap[ImGuiKey_J] = OE_KEY_J;
		io.KeyMap[ImGuiKey_K] = OE_KEY_K;
		io.KeyMap[ImGuiKey_L] = OE_KEY_L;
		io.KeyMap[ImGuiKey_M] = OE_KEY_M;
		io.KeyMap[ImGuiKey_N] = OE_KEY_N;
		io.KeyMap[ImGuiKey_O] = OE_KEY_O;
		io.KeyMap[ImGuiKey_P] = OE_KEY_P;
		io.KeyMap[ImGuiKey_Q] = OE_KEY_Q;
		io.KeyMap[ImGuiKey_R] = OE_KEY_R;
		io.KeyMap[ImGuiKey_S] = OE_KEY_S;
		io.KeyMap[ImGuiKey_T] = OE_KEY_T;
		io.KeyMap[ImGuiKey_U] = OE_KEY_U;
		io.KeyMap[ImGuiKey_V] = OE_KEY_V;
		io.KeyMap[ImGuiKey_W] = OE_KEY_W;
		io.KeyMap[ImGuiKey_X] = OE_KEY_X;
		io.KeyMap[ImGuiKey_Y] = OE_KEY_Y;
		io.KeyMap[ImGuiKey_Z] = OE_KEY_Z;

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

		io.KeyCtrl = io.KeysDown[OE_KEY_LEFT_CONTROL] || io.KeysDown[OE_KEY_RIGHT_CONTROL];
		io.KeyAlt = io.KeysDown[OE_KEY_LEFT_ALT] || io.KeysDown[OE_KEY_RIGHT_ALT];
		io.KeyShift = io.KeysDown[OE_KEY_LEFT_SHIFT] || io.KeysDown[OE_KEY_RIGHT_SHIFT];
		io.KeySuper = io.KeysDown[OE_KEY_LEFT_SUPER] || io.KeysDown[OE_KEY_RIGHT_SUPER];

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