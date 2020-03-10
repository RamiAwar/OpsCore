#include "ocpch.h"
#include "OpsCore/Platform/OpenGL/OpenGLTexture.h"
#include "OpsCore/Utils/stb_image.h"
#include "OpsCore/Platform/OpenGL/OpenGLMacros.h"

#include <glad/glad.h>

namespace oc {
	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
		:m_Path(path), m_Width(0), m_Height(0)
	{
		int width, height, channels;

		stbi_set_flip_vertically_on_load(1); // flip image upon loading
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		// We might get 4 or 3 channels ( with or without alpha channel)
		
		// OC_ASSERT(data, "Failed to load image!");
		if(!data) {
			OC_INFO("Failed to load image!");
			// OC_INFO("Current working directory: '{0}'", GetCurrentWorkingDir());
			return;
		}
		
		m_Width = width;
		m_Height = height;

		GLenum internalFormat = 0, dataFormat = 0; // initialize
		if (channels == 4) {
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		else if (channels == 3) {
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}

		OC_ASSERT(internalFormat && dataFormat, "Image format trying to load is not supported!");

		#ifdef OC_PLATFORM_WINDOWS

			GLCall(glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID));
			GLCall(glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height));

			GLCall(glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
			GLCall(glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

			GLCall(glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data));
	
		#elif defined(OC_PLATFORM_MACOS)
			GLCall(glGenTextures(1, &m_RendererID));
			GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
			GLCall(glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Width, m_Height, 0, dataFormat, GL_UNSIGNED_BYTE, data));
			GLCall(glGenerateMipmap(GL_TEXTURE_2D));
		#endif

		// No retain method
		stbi_image_free(data); // clears data pointer
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		GLCall(glDeleteTextures(1, &m_RendererID));
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		#ifdef OC_PLATFORM_WINDOWS
			GLCall(glBindTextureUnit(slot, m_RendererID));
		#elif defined(OC_PLATFORM_MACOS)
			GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
		#endif
	}

	/*void OpenGLTexture2D::SetMagnification(TextureMag textMag)
	{
		switch (textMag) {
		case Texture2D::TextureMag::NEAREST:
			glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		case Texture2D::TextureMag::LINEAR:
			glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		default:
			OC_ASSERT(false, "Unknown texture magnification setting!");
		}
	}

	void OpenGLTexture2D::SetMinification(TextureMag textMag)
	{
		switch (textMag) {
		case Texture2D::TextureMag::NEAREST:
			glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		case Texture2D::TextureMag::LINEAR:
			glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		default:
			OC_ASSERT(false, "Unknown texture minification setting!");
		}
	}
*/

}
