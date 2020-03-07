#include "ocpch.h"
#include "OpenGLTexture.h"
#include "OpsCore/Utils/stb_image.h"

#include <glad/glad.h>

namespace oc {
	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
		:m_Path(path), m_Width(0), m_Height(0)
	{
		int width, height, channels;

		stbi_set_flip_vertically_on_load(1); // flip image upon loading
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		
		OC_ASSERT(data, "Failed to load image!");
		
		m_Width = width;
		m_Height = height;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, GL_RGB8, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, GL_RGB, GL_UNSIGNED_BYTE, data);
		// Retain or dont retain?

		// No retain method
		stbi_image_free(data); // clears data pointer
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, m_RendererID);
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
