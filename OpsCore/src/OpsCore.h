#pragma once

// For use by applications
#include "OpsCore/Application.h"

#include "OpsCore/Layer.h" // Just here for clarity
#include "OpsCore/ImGui/ImGuiLayer.h"


// ------- CORE ----------------------
#include "OpsCore/Core/Timestep.h"
#include "OpsCore/Renderer/Cameras/OrthographicCameraController.h"


// ------- RENDERING ------------------
#include "OpsCore/Renderer/Buffer.h"
#include "OpsCore/Renderer/VertexArray.h"
#include "OpsCore/Renderer/Shader.h"
#include "OpsCore/Platform/OpenGL/OpenGLShader.h"
#include "OpsCore/Renderer/RenderCommand.h"
#include "OpsCore/Renderer/Renderer.h"
#include "OpsCore/Renderer/Cameras/OrthographicCamera.h"
#include "OpsCore/Renderer/Texture.h"


// ------- IMGUI ----------------------
#include "OpsCore/ImGui/ImGuiWidgets.h"
#include "OpsCore/ImGui/ImGuiFileDialog.h"

// ------------ Input -------------
#include "OpsCore/Input.h"
#include "OpsCore/KeyCodes.h"
#include "OpsCore/MouseButtonCodes.h"

// ------- Entry point -----------
#include "OpsCore/Entrypoint.h"
// -------------------------------
