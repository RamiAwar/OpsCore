#pragma once

#include <string>
#include <glm/glm.hpp>

namespace oc {


	class Shader {

	public:

		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual const std::string& GetName() const = 0;
		static std::shared_ptr<Shader> Create(const std::string& filepath);
		static std::shared_ptr<Shader> Create(const std::string name, const std::string& vertexSrc, const std::string& fragmentSrc);


		virtual void SetInt(const std::string name, const int& value) = 0;
		virtual void SetFloat(const std::string name, const float& value) = 0;
		virtual void SetFloat2(const std::string name, const glm::vec2& value) = 0;
		virtual void SetFloat3(const std::string name, const glm::vec3& value) = 0;
		virtual void SetFloat4(const std::string name, const glm::vec4& value) = 0;
		virtual void SetMat4(const std::string name, const glm::mat4& value) = 0;

	};

	/*
	A class that provides primitive shaders.

	This class exists to provide a better user experience for OpsCore's users 
	by providing a robust implementation of some primitive shaders.
	Clients that need to write their own shaders are also welcome to do so and add 
	them to the library.

	*/
	class ShaderLibrary {
	public:

		void Add(const std::shared_ptr<Shader>& shader);
		void Add(const std::string name, const std::shared_ptr<Shader>& shader);

		std::shared_ptr<Shader> Load(const std::string& filepath); // assets/Texture.glsl - strips name from path
		std::shared_ptr<Shader> Load(const std::string name, const std::string& filepath); // name provided manually
		std::shared_ptr<Shader> Get(const std::string& name); // retrieves shader from map by name

		bool Find(const std::string& name) const;

		// TODO: REMOVE DEBUG FUNCTION 
		void _List() const;

	private:
		std::unordered_map<std::string, std::shared_ptr<Shader>> m_Shaders;
	};

}