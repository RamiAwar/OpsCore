#pragma once

#include "OpsCore/Core/Core.h"

namespace oc {

	class Texture {

	public:

		virtual ~Texture() = default;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual uint32_t GetRendererID() const = 0;

		virtual void SetData(void* data, uint32_t size) = 0;

		virtual void Bind(uint32_t slot = 0) const = 0;
	};

	class Texture2D : public Texture { // also abstract, no implementations except for 2D texture specifics
	public:
		
		enum class TextureMag {
			NEAREST,
			LINEAR
		};

		static std::shared_ptr<Texture2D> Create(const std::string& path);
		static Ref<Texture2D> Create(uint32_t width, uint32_t height);
		//virtual void SetMagnification(TextureMag textMag) = 0;
		//virtual void SetMinification(TextureMag textMag) = 0;
	};
}