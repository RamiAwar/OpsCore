#include "EditorApp.h"


float EditorLayer::m_FPS = 0.0f;
int EditorLayer::fps_counter = 0;


// TODO: Refactor this aspect ratio implementation
EditorLayer::EditorLayer() : Layer("Example"),
m_GameLayer(GameLayer()),
m_ViewportActive(false)
{
	PB_CLIENT_INFO("Constructing Editor Layer");
}

void EditorLayer::OnAttach()
{
	// Initialize viewport framebuffer
	m_Framebuffer.reset(pb::Framebuffer::Create(1280, 720, pb::FramebufferFormat::RGBA16F));

	m_GameLayer.OnAttach();
}

void EditorLayer::OnDetach()
{
	m_GameLayer.OnDetach();
}

void EditorLayer::OnUpdate(pb::Timestep ts)
{

	PB_PROFILE_FUNCTION();

	// UPDATE
	{
		PB_PROFILE_VISUAL_SCOPE("CameraController::Update");
		if (m_ViewportActive) {
			m_GameLayer.OnUpdate(ts);
		}
	}

	// TODO: do more efficiently
	// FPS counting
	fps_counter++;
	if (fps_counter % 50 == 0) m_FPS = 1.0f / ts;
	if (fps_counter > 10000000) fps_counter = 0;


	// RENDER
	{
		PB_PROFILE_SCOPE("Renderer2D Loop");
		{
			PB_PROFILE_VISUAL_SCOPE("Renderer2D E2E");
			m_Framebuffer->Bind();
			m_GameLayer.OnRender();
			m_Framebuffer->Unbind();
		}
	}
}

void EditorLayer::OnEvent(pb::Event& event) {

	//PB_PROFILE_FUNCTION();
	//PB_CLIENT_TRACE("{0}", event);
	if (m_ViewportActive) {
		m_GameLayer.OnEvent(event);
	}


}


void EditorLayer::OnImGuiRender() {

	//PB_PROFILE_FUNCTION();

	// ------- Color Settings Menu ---------
	static bool p_open = true; // has to be static because this is called every frame. 
	/* each time the function is called the static variable will maintain the last
	value it had at the end of the previous function call. */

	static bool display_dialog = false;

	static bool opt_fullscreen_persistant = true;
	static ImGuiDockNodeFlags opt_flags = ImGuiDockNodeFlags_None;
	bool opt_fullscreen = opt_fullscreen_persistant;

	// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
	// because it would be confusing to have two docking targets within each others.
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
	if (opt_fullscreen)
	{
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->Pos);
		ImGui::SetNextWindowSize(viewport->Size);
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	}

	// When using ImGuiDockNodeFlags_PassthruDockspace, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
	if (opt_flags & ImGuiDockNodeFlags_PassthruCentralNode)
		window_flags |= ImGuiWindowFlags_NoBackground;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("DockSpace Demo", &p_open, window_flags);
	ImGui::PopStyleVar();

	if (opt_fullscreen)
		ImGui::PopStyleVar(2);

	// Dockspace
	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
	{
		ImGuiID dockspace_id = ImGui::GetID("MyDockspace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), opt_flags);
	}


	m_GameLayer.OnImGuiRender();

	ImGui::Begin("Settings");
	if (ImGui::TreeNode("Shaders"))
	{
		auto& shaders = pb::ShaderLibrary::GetInstance()->m_Shaders;
		for (auto& shader : shaders)
		{
			if (ImGui::TreeNode(shader.first.c_str()))
			{
				std::string buttonName = "Reload##" + shader.first;
				if (ImGui::Button(buttonName.c_str()))
					shader.second->Reload();
				ImGui::TreePop();
			}
		}
		ImGui::TreePop();
	}
	ImGui::End();

	PB_PROFILE_RENDER();

	ImGui::Begin("Stats");
	ImGui::Text("FPS: %.2f", m_FPS);
	ImGui::End();

	ImGui::Begin("Viewport");

	m_ViewportActive = ImGui::IsWindowFocused();

	auto viewportSize = ImGui::GetContentRegionAvail();
	m_Framebuffer->Resize((uint32_t)viewportSize.x, (uint32_t)viewportSize.y);
	m_Framebuffer->Resize((uint32_t)viewportSize.x, (uint32_t)viewportSize.y);
	ImGui::Image((void*)m_Framebuffer->GetColorAttachmentRendererID(), viewportSize, { 0, 1 }, { 1, 0 });
	ImGui::End();


	ImGui::End();

}


class Editor : public pb::Scene {
public:
	Editor(){}

	void OnAttach() {
		PushLayer(new EditorLayer());
	}

	~Editor() {}
};

class Main : public pb::Application {
public:

	Main() 
	{
		pb::SceneStateMachine::instance()->Add("test", pb::CreateRef<Editor>());
	}

	~Main() {};

};

// Defining CreateApplication in client
pb::Application* pb::CreateApplication() 
{	
	return new Main();
}

