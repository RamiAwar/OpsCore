#include "ocpch.h"
#include "OpenGLShader.h"

#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>
#include "OpsCore/Utils/Path.h"

#include "OpenGLMacros.h"

static GLenum ShaderTypeFromString(const std::string& type) {
	if (type == "vertex") {
		return GL_VERTEX_SHADER;
	}
	else if (type == "fragment" || type == "pixel") {
		return GL_FRAGMENT_SHADER;
	}
	OC_ASSERT(false, "Unknown shader type specified.");
	return 0;
}


oc::OpenGLShader::OpenGLShader(const std::string& filepath)
{
	std::string source = ReadFile(filepath);
	// Do not attempt to compile shader if file is not read ( empty string )
	if (!source.empty()) {
		auto shaderSources = Preprocess(source);
		Compile(shaderSources);
	}

	// assets/shaders/Texture.shader.glsl
	Path path(filepath);
	m_Name = path.basename_strip_extension().str();

}

oc::OpenGLShader::OpenGLShader(const std::string name, const std::string& vertexSrc, const std::string& fragmentSrc)
	: m_Name(name)
{
	std::unordered_map<GLenum, std::string> sources;
	sources[GL_VERTEX_SHADER] = vertexSrc;
	sources[GL_FRAGMENT_SHADER] = fragmentSrc;
	Compile(sources);

}

oc::OpenGLShader::~OpenGLShader()
{
	GLCall(glDeleteProgram(m_RendererID));
}

void oc::OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources) 
{
	
	GLuint program = glCreateProgram();

	OC_ASSERT(shaderSources.size() <= 2, "Exactly 2 shaders needed to compile shader. Support for more than one vertex and one fragment shader is not available.");

	std::array<GLenum, 2> shaderIDs;
	int index = 0;
	for (auto& kv : shaderSources) {

		GLenum type = kv.first;
		const std::string& source = kv.second;

		// Create an empty #type shader handle
		GLuint shader = glCreateShader(type);

		// Send the #type shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const GLchar* source_cstr = (const GLchar*)source.c_str();
		GLCall(glShaderSource(shader, 1, &source_cstr, 0));
		// Compile the #type shader
		GLCall(glCompileShader(shader));

		GLint isCompiled = 0;
		GLCall(glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled));
		if (isCompiled == GL_FALSE) {
			GLint maxLength = 0;
			GLCall(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength));

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			GLCall(glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]));

			// We don't need the shader anymore.
			GLCall(glDeleteShader(shader));

			// Use the infoLog as you see fit.
			OC_ERROR("{0}", infoLog.data());
			OC_ASSERT(false, "Shader compilation failure!");

			break;
		}

		GLCall(glAttachShader(program, shader));
		shaderIDs[index++] = shader;

	}

	m_RendererID = program;

	// Link our m_RendererID
	GLCall(glLinkProgram(m_RendererID));

	// Note the different functions here: GLCall(glGetProgram* instead of GLCall(glGetShader*.
	GLint isLinked = 0;
	GLCall(glGetProgramiv(m_RendererID, GL_LINK_STATUS, (int*)&isLinked));
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		GLCall(glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &maxLength));

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		GLCall(glGetProgramInfoLog(m_RendererID, maxLength, &maxLength, &infoLog[0]));

		// We don't need the m_RendererID anymore.
		GLCall(glDeleteProgram(m_RendererID));
		// Don't leak shaders either.
		for (auto id : shaderIDs) {
			GLCall(glDeleteShader(id));
		}
		// Use the infoLog as you see fit.

		OC_ERROR("{0}", infoLog.data());
		OC_ASSERT(false, "Shader linking failure!");

		return;
	}

	// Always detach shaders after a successful link.
	for (auto id : shaderIDs) {
		GLCall(glDetachShader(m_RendererID, id));
	}
	
}


void oc::OpenGLShader::Bind() const
{
	GLCall(glUseProgram(m_RendererID));
}

void oc::OpenGLShader::Unbind() const
{
	GLCall(glUseProgram(0));
}

void oc::OpenGLShader::UploadUniformInt(const std::string& name, const int value)
{
	GLint location = glGetUniformLocation(m_RendererID, name.c_str());
	GLCall(glUniform1i(location, value));
}

void oc::OpenGLShader::UploadUniformFloat(const std::string& name, const float value)
{
	GLint location = glGetUniformLocation(m_RendererID, name.c_str());
	GLCall(glUniform1f(location, value));
}

void oc::OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& value)
{
	GLint location =glGetUniformLocation(m_RendererID, name.c_str());
	GLCall(glUniform2f(location, value.x, value.y));
}

void oc::OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& value)
{
	GLint location = glGetUniformLocation(m_RendererID, name.c_str());
	GLCall(glUniform3f(location, value.x, value.y, value.z));
}

void oc::OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& value)
{
	GLint location = glGetUniformLocation(m_RendererID, name.c_str());
	GLCall(glUniform4f(location, value.x, value.y, value.z, value.w));
}

void oc::OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix)
{
	GLint location = glGetUniformLocation(m_RendererID, name.c_str());
	GLCall(glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix)));
}

void oc::OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix) {
	GLint location = glGetUniformLocation(m_RendererID, name.c_str());
	GLCall(glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix)));
}

std::string oc::OpenGLShader::ReadFile(const std::string& filepath) {
	std::string result;
	std::ifstream in(filepath, std::ios::in | std::ios::binary);
	if (in) {
		in.seekg(0, std::ios::end);
		result.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&result[0], result.size());
		in.close();
	}
	else {
		OC_ERROR("Could not open file '{0}'", filepath);
	}
	return result;
}


// TODO: REWRITE THIS CODE TO BE MORE ROBUST
std::unordered_map<GLenum, std::string> oc::OpenGLShader::Preprocess(const std::string& source) {

	std::unordered_map<GLenum, std::string> shaderSource;
	
	// Split file into vertex and fragment shaders by preprocessor directive #type
	const char* typeToken = "#type";
	size_t typeTokenLength = strlen(typeToken);
	size_t pos = source.find(typeToken, 0);
	while (pos != std::string::npos) {
		size_t eol = source.find_first_of("\r\n", pos);
		OC_ASSERT(eol != std::string::npos, "Syntax error in parsing shader file.");

		size_t begin = pos + typeTokenLength + 1;
		std::string type = source.substr(begin, eol - begin);
		OC_ASSERT(type == "vertex" || type == "fragment" || type == "pixel", "Invalid shader type specified.");

		size_t nextLinePos = source.find_first_not_of("\r\n", eol);
		OC_ASSERT(nextLinePos != std::string::npos, "Syntax error in parsing shader file!");
		pos = source.find(typeToken, nextLinePos);

		shaderSource[ShaderTypeFromString(type)] = 
			(pos == std::string::npos) ? source.substr(nextLinePos) : source.substr(nextLinePos, pos - nextLinePos);
	}

	return shaderSource;
}











