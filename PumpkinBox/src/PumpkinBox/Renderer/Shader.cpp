#include "pbpch.h"

#include "Shader.h"
#include "RendererAPI.h"

#include "PumpkinBox/Platform/OpenGL/OpenGLShader.h"

namespace pb {

	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		switch (RendererAPI::GetAPI()) {
		case RendererAPI::API::None:
			PB_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLShader>(filepath);
		default:
			PB_ASSERT(false, "Unknown RendererAPI!");
			return nullptr;
		}
		return nullptr;
	}
	Ref<Shader> Shader::Create(const std::string name, const std::string& vertexSrc, const std::string& fragmentSrc) {

		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None:
			PB_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLShader>(name, vertexSrc, fragmentSrc);
		default:
			PB_ASSERT(false, "Unknown RendererAPI!");
			return nullptr;
		} 
	}

	ShaderLibrary* ShaderLibrary::s_Instance = new ShaderLibrary();

	void ShaderLibrary::Add(const std::string name, const Ref<Shader>& shader)
	{
		PB_ASSERT(!Find(name), "Shader already exists in library.");
		m_Shaders[name] = shader;
	}

	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		auto& name = shader->GetName();
		Add(name, shader);
	}


	Ref<Shader> ShaderLibrary::Load(const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		if (Find(shader->GetName())) { return shader; }
		else {
			Add(shader);
			return shader;
		}
	}

	Ref<Shader> ShaderLibrary::Load(const std::string name, const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		if (Find(shader->GetName())) { return shader; }
		else {
			Add(name, shader);
			return shader;
		}
	}

	Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
		PB_ASSERT(Find(name), "Shader Library Error: Shader {} does not exist in this library.", name);
		return m_Shaders[name];
	}

	bool ShaderLibrary::Find(const std::string& name) const
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}


	// TODO: REMOVE DEBUG FUNCTION
	void ShaderLibrary::_List() const {
		for (auto i : m_Shaders) {
			PB_INFO("+++");
			PB_INFO("shader {}", i.first);
			PB_INFO("===");
		}
	}

}