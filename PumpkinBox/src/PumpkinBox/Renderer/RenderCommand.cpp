#include "pbpch.h"
#include "RenderCommand.h"

#include "PumpkinBox/Platform/OpenGL/OpenGLRendererAPI.h"

namespace pb {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;


}