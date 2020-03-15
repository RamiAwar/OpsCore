#include "ocpch.h"
#include "OpsCore/Platform/OpenGL/OpenGLTexture.h"
#include "OpsCore/Utils/stb_image.h"
#include "OpsCore/Platform/OpenGL/OpenGLMacros.h"


namespace oc {

	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height)
		:m_Width(width), m_Height(height)
	{
		m_InternalFormat = GL_RGBA8;
		m_DataFormat = GL_RGBA; 

		#ifdef OC_PLATFORM_WINDOWS

		GLCall(glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID));
		GLCall(glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height));

		GLCall(glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCall(glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

		// Wrapping textures
		GLCall(glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
		GLCall(glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT));
		GLCall(glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT));


		// Edge clamp (repeat edge pixels infinitely)
		//GLCall(glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		//GLCall(glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

		#elif defined(OC_PLATFORM_MACOS)
		GLCall(glGenTextures(1, &m_RendererID));
		GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		#endif
	}

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

		if (channels == 4) {
			m_InternalFormat = GL_RGBA8;
			m_DataFormat = GL_RGBA;
		}
		else if (channels == 3) {
			m_InternalFormat = GL_RGB8;
			m_DataFormat = GL_RGB;
		}

		OC_ASSERT(m_InternalFormat && m_DataFormat, "Image format trying to load is not supported!");

		#ifdef OC_PLATFORM_WINDOWS

			GLCall(glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID));
			GLCall(glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height));

			GLCall(glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
			GLCall(glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
			
			// Wrapping textures
			GLCall(glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
			GLCall(glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT));
			GLCall(glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT));


			// Edge clamp (repeat edge pixels infinitely)
			//GLCall(glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
			//GLCall(glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));


			GLCall(glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data));
	
		#elif defined(OC_PLATFORM_MACOS)
			GLCall(glGenTextures(1, &m_RendererID));
			GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
			GLCall(glTexImage2D(GL_TEXTURE_2D, 0, m_InternalFormat, m_Width, m_Height, 0, m_DataFormat, GL_UNSIGNED_BYTE, data));
			GLCall(glGenerateMipmap(GL_TEXTURE_2D));
		#endif

		// No retain method
		stbi_image_free(data); // clears data pointer
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		GLCall(glDeleteTextures(1, &m_RendererID));
	}

	void OpenGLTexture2D::SetData(void* data, uint32_t size)
	{
		// Check input data
		uint32_t bytes_per_channel = m_DataFormat == GL_RGBA ? 4 : 3;
		OC_ASSERT(size == m_Width * m_Height * bytes_per_channel, "Data passed in OpenGLTexture2D::SetData must be entire texture! Missing values!");

		#ifdef OC_PLATFORM_WINDOWS
			GLCall(glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data));
		#elif defined(OC_PLATFORM_MACOS)
			GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
			GLCall(glTexImage2D(GL_TEXTURE_2D, 0, m_InternalFormat, m_Width, m_Height, 0, m_DataFormat, GL_UNSIGNED_BYTE, data));
			GLCall(glGenerateMipmap(GL_TEXTURE_2D));
		#endif
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
