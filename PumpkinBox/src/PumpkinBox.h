#pragma once

// For use by applications
#include "PumpkinBox/Core/Application.h"

#include "PumpkinBox/Core/Layer.h" // Just here for clarity
#include "PumpkinBox/ImGui/ImGuiLayer.h"

// ------- RENDERING ------------------
#include "PumpkinBox/Renderer/Buffer.h"
#include "PumpkinBox/Renderer/VertexArray.h"
#include "PumpkinBox/Renderer/Shader.h"
#include "PumpkinBox/Platform/OpenGL/OpenGLShader.h"
#include "PumpkinBox/Renderer/RenderCommand.h"
#include "PumpkinBox/Renderer/Renderer.h" 
#include "PumpkinBox/Renderer/Renderer2D.h"
#include "PumpkinBox/Renderer/Texture.h"

// ------- CORE ----------------------
#include "PumpkinBox/Core/Timestep.h"
#include "PumpkinBox/Renderer/Cameras/OrthographicCameraController.h"
#include "PumpkinBox/Renderer/Cameras/OrthographicCamera.h"
#include "PumpkinBox/Core/Scene.h"
#include "PumpkinBox/Core/SceneStateMachine.h"
#include "PumpkinBox/Core/Sprite.h"
#include "PumpkinBox/Core/Animation2D.h"

// ------ CORE Data Structures ------
#include "PumpkinBox/Core/VVector.h"


// ------- ECS ----------------------
#include "PumpkinBox/Core/ECS/World.h"
#include "PumpkinBox/Core/ECS/Components/MovementSystem.h"


// ------- IMGUI ----------------------
#include "PumpkinBox/ImGui/ImGuiFileDialog.h"

// ------------ Input -------------
#include "PumpkinBox/Core/Input.h"
#include "PumpkinBox/Core/KeyCodes.h"
#include "PumpkinBox/Core/MouseButtonCodes.h"

// -------- Libraries
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"

// -------------------------------
