#pragma once

// For use by applications
#include "OpsCore/Core/Application.h"

#include "OpsCore/Core/Layer.h" // Just here for clarity
#include "OpsCore/ImGui/ImGuiLayer.h"

// ------- CORE ----------------------
#include "OpsCore/Core/Timestep.h"
#include "OpsCore/Renderer/Cameras/OrthographicCameraController.h"
#include "OpsCore/Core/Scene.h"
#include "OpsCore/Core/SceneStateMachine.h"


// ------- RENDERING ------------------
#include "OpsCore/Renderer/Buffer.h"
#include "OpsCore/Renderer/VertexArray.h"
#include "OpsCore/Renderer/Shader.h"
#include "OpsCore/Platform/OpenGL/OpenGLShader.h"
#include "OpsCore/Renderer/RenderCommand.h"
#include "OpsCore/Renderer/Renderer.h"
#include "OpsCore/Renderer/Renderer2D.h"
#include "OpsCore/Renderer/Cameras/OrthographicCamera.h"
#include "OpsCore/Renderer/Texture.h"


// ------- IMGUI ----------------------
#include "OpsCore/ImGui/ImGuiFileDialog.h"

// ------------ Input -------------
#include "OpsCore/Core/Input.h"
#include "OpsCore/Core/KeyCodes.h"
#include "OpsCore/Core/MouseButtonCodes.h"

// -------- Libraries
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"

// -------------------------------
