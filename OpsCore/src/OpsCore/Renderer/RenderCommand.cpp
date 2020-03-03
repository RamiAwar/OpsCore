#include "ocpch.h"
#include "RenderCommand.h"

#include "OpsCore/Platform/OpenGL/OpenGLRendererAPI.h"

namespace oc {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;


}