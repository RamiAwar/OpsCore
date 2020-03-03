#include "ocpch.h"
#include "ImGuiLayer.h"

#include "imgui.h"

#include "examples/imgui_impl_opengl3.h"
#include "examples/imgui_impl_glfw.h"

#include "OpsCore/Application.h"

// TODO: REMOVE
#include "GLFW/glfw3.h"
#include "glad/glad.h"

namespace oc {

	ImGuiLayer::ImGuiLayer() 
		:Layer("ImGuiLayer")
	{
	}

	ImGuiLayer::~ImGuiLayer()
	{
	}

	void ImGuiLayer::OnAttach()
	{
		
		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
		//io.ConfigViewportsNoAutoMerge = true;
		//io.ConfigViewportsNoTaskBarIcon = true;

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsClassic();

		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		Application& app = Application::Get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

		// Setup Platform/Renderer bindings
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 410");

	}

	void ImGuiLayer::OnDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}



	void ImGuiLayer::Begin() {
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiLayer::End() {
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2((float) app.GetWindow().GetWidth(), (float) app.GetWindow().GetHeight());

		// Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}

	void ImGuiLayer::OnImGuiRender() {

		static bool show = false;

		ImGui::ShowDemoWindow(&show);
	}

	/*void ImGuiLayer::OnUpdate()
	{
		
		ImGuiIO& io = ImGui::GetIO();
		float time = (float)glfwGetTime();
		io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
		m_Time = time;

		Application& app = Application::Get();
		io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();
		

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}*/

	//void ImGuiLayer::OnEvent(Event& event)
	//{
	//	EventDispatcher dispatcher(event);
	//	dispatcher.Dispatch<MouseButtonPressedEvent>(OC_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressedEvent));
	//	dispatcher.Dispatch<MouseButtonReleasedEvent>(OC_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleasedEvent));
	//	dispatcher.Dispatch<MouseMovedEvent>(OC_BIND_EVENT_FN(ImGuiLayer::OnMouseMovedEvent));
	//	dispatcher.Dispatch<MouseScrolledEvent>(OC_BIND_EVENT_FN(ImGuiLayer::OnMouseScrolledEvent));
	//	dispatcher.Dispatch<KeyPressedEvent>(OC_BIND_EVENT_FN(ImGuiLayer::OnKeyPressedEvent));
	//	dispatcher.Dispatch<KeyTypedEvent>(OC_BIND_EVENT_FN(ImGuiLayer::OnKeyTypedEvent));

	//	dispatcher.Dispatch<WindowResizeEvent>(OC_BIND_EVENT_FN(ImGuiLayer::OnWindowResizeEvent));
	//	dispatcher.Dispatch<WindowCloseEvent>(OC_BIND_EVENT_FN(ImGuiLayer::OnWindowCloseEvent));

	//}
	//bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
	//{
	//	ImGuiIO& io = ImGui::GetIO();
	//	io.MouseDown[e.GetMouseButton()] = true;

	//	return false; // we haven't handled this -> want other layers be able to handle this: dont consume it for now
	//}

	//bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
	//{
	//	ImGuiIO& io = ImGui::GetIO();
	//	io.MouseDown[e.GetMouseButton()] = false;
	//	return false;
	//}

	//bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& e)
	//{
	//	ImGuiIO& io = ImGui::GetIO();
	//	io.MousePos = ImVec2(e.GetX(), e.GetY());

	//	return false;
	//}
	//bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& e)
	//{
	//	ImGuiIO& io = ImGui::GetIO();
	//	io.MouseWheel += e.GetYOffset();
	//	io.MouseWheelH += e.GetXOffset();
	//	return false;
	//}
	//bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& e)
	//{
	//	ImGuiIO& io = ImGui::GetIO();
	//	io.KeysDown[e.GetKeyCode()] = true;

	//	io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
	//	io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
	//	io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
	//	io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
	//	return false;
	//}

	//bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& e) {
	//	ImGuiIO& io = ImGui::GetIO();
	//	int keycode = e.GetKeyCode();
	//	if (keycode > 0 && keycode < 0x10000) {
	//		io.AddInputCharacter((unsigned short)keycode);
	//	}
	//	return false;
	//}

	//bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& e)
	//{
	//	return false;
	//}
	//bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent& e)
	//{
	//	ImGuiIO& io = ImGui::GetIO();
	//	io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
	//	io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
	//	glViewport(0, 0, e.GetWidth(), e.GetHeight());

	//	return false;
	//}
	//bool ImGuiLayer::OnWindowCloseEvent(WindowCloseEvent& e)
	//{
	//	return false;
	//}
}