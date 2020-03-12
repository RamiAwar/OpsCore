#include "ocpch.h"

#include "Shader.h"
#include "RendererAPI.h"

#include "OpsCore/Platform/OpenGL/OpenGLShader.h"

namespace oc {
	std::shared_ptr<Shader> Shader::Create(const std::string& filepath)
	{
		switch (RendererAPI::GetAPI()) {
		case RendererAPI::API::None:
			OC_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLShader>(filepath);
		default:
			OC_ASSERT(false, "Unknown RendererAPI!");
			return nullptr;
		}
		return nullptr;
	}
	std::shared_ptr<Shader> Shader::Create(const std::string name, const std::string& vertexSrc, const std::string& fragmentSrc) {

		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None:
			OC_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLShader>(name, vertexSrc, fragmentSrc);
		default:
			OC_ASSERT(false, "Unknown RendererAPI!");
			return nullptr;
		} 
	}

	void ShaderLibrary::Add(const std::string name, const std::shared_ptr<Shader>& shader)
	{
		OC_ASSERT(!Find(name), "Shader already exists in library.");
		m_Shaders[name] = shader;
	}

	void ShaderLibrary::Add(const std::shared_ptr<Shader>& shader)
	{
		auto& name = shader->GetName();
		Add(name, shader);
	}


	std::shared_ptr<Shader> ShaderLibrary::Load(const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		if (Find(shader->GetName())) { return shader; }
		else {
			Add(shader);
			return shader;
		}
	}

	std::shared_ptr<Shader> ShaderLibrary::Load(const std::string name, const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		if (Find(shader->GetName())) { return shader; }
		else {
			Add(name, shader);
			return shader;
		}
	}

	std::shared_ptr<Shader> ShaderLibrary::Get(const std::string& name)
	{
		OC_ASSERT(Find(name), "Shader does not exist in this library.");
		return m_Shaders[name];
	}
	bool ShaderLibrary::Find(const std::string& name) const
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}
}