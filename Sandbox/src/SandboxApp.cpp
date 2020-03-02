
#include <OpsCore.h>
#include "imgui.h"
#include <glad/glad.h>


unsigned int buffer;
float vertexPositions[6] = {
-0.5f, -0.5f,
 0.0f,  0.5f,
 0.5f, -0.5f
};

class ExampleLayer : public oc::Layer {
public:
	ExampleLayer() : Layer("Example") {
		
		OC_CLIENT_INFO("ExampleLayer::Setting up OpenGL states");

		glGenBuffers(1, &buffer); // Generate one buffer, unspecified type yet

		glBindBuffer(GL_ARRAY_BUFFER, buffer); // specify type of buffer: just an array

		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6, &vertexPositions, GL_STATIC_DRAW); // Set buffer size and fill it
	}

	void OnUpdate() override { 
		//OC_CLIENT_INFO("ExampleLayer::Update"); 

		/*if (oc::Input::IsKeyPressed(OC_KEY_TAB)) {

			OC_CLIENT_TRACE("TAB key is pressed");
		}*/

		
		glDrawArrays(GL_TRIANGLES, 0, 3);
		





	}

	void OnEvent(oc::Event& event) override { 
		//OC_CLIENT_TRACE("{0}", event); 
	}

	virtual void OnImGuiRender() override {

		static ImGuiID dockspaceID = 0;
		bool active = true;
		if (ImGui::Begin("Master Window", &active))
		{
			ImGui::TextUnformatted("DockSpace below");
		}
		if (active)
		{
			// Declare Central dockspace
			dockspaceID = ImGui::GetID("HUB_DockSpace");
			ImGui::DockSpace(dockspaceID, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None | ImGuiDockNodeFlags_PassthruCentralNode/*|ImGuiDockNodeFlags_NoResize*/);

		}
		ImGui::End();

		ImGui::SetNextWindowDockID(dockspaceID, ImGuiCond_FirstUseEver);
		if (ImGui::Begin("Dockable Window"))
		{
			ImGui::TextUnformatted("Test");
			const ImU32 col = ImGui::GetColorU32(ImGuiCol_ButtonHovered);
			const ImU32 bg = ImGui::GetColorU32(ImGuiCol_Button);

			ImGui::Spinner("##spinner", 20.0f, col, bg, 10, 10.0f, 20.0f);
			//ImGui::BufferingBar("##buffer_bar", 0.7f, ImVec2(400, 6), bg, col);
		}
		ImGui::End();

	}

};

class Sandbox : public oc::Application {
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
	}

	~Sandbox() {}

};


// Defining CreateApplication in client
oc::Application* oc::CreateApplication() {
	return new Sandbox();
}