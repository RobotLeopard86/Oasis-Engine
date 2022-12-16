#include "OasisPCH.h"
#include "ImGuiLayer.h"
#include "ImGuiCustomStyle.h"

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "OasisEngine/Application.h"

#include "OasisEngine/Keycodes.h"
#include "OasisEngine/Input.h"

//TEMPORARY
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Oasis {

	ImGuiLayer::ImGuiLayer()
		: Layer("ImGui Layer") {}

	ImGuiLayer::~ImGuiLayer() {}

	void ImGuiLayer::OnInit() {
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiStyleOasis();

		Application& app = Application::Get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		ImGui_ImplGlfw_InitForOpenGL(window, true);
		succesfulImGuiInit = ImGui_ImplOpenGL3_Init("#version 410");
		OE_COREASSERT(succesfulImGuiInit, "ImGui refused to initialize!");
	}

	void ImGuiLayer::OnShutdown() {
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::Begin() {
		//Backup ImGui intialization in case it wasn't properly initialized before
		if(!succesfulImGuiInit) {
			OE_CORE_WARN("ImGui did not properly initialize before new frame, initializing now.");
			ImGui::CreateContext();
			ImGuiStyleOasis();
			Application& app = Application::Get();
			GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());
			ImGui_ImplGlfw_InitForOpenGL(window, true);
			succesfulImGuiInit = ImGui_ImplOpenGL3_Init("#version 410");
			OE_COREASSERT(succesfulImGuiInit, "Backup ImGui initialization failed!")
		}
		
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiLayer::End() {
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2(app.GetWindow().GetWindowWidth(), app.GetWindow().GetWindowHeight());

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if(io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
			GLFWwindow* backupContext = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backupContext);
		}
	}

	void ImGuiLayer::OnImGuiDraw() {
		static bool showDemoWindow = true;
		ImGui::ShowDemoWindow(&showDemoWindow);
	}
}