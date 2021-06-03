#pragma once

#include "../Core/Includes.h"
#include "../../Vendor/stb_image.h"
#include "../Core/DataStructures.h"

namespace MachGL {
	namespace Graphics {

		enum class ImageType {

			RGB, RGBA
		};

		enum class GLTextureType {

			CUBE
		};

		class Image {

			protected:
				int				         m_width	= 0;
                int				         m_height	= 0;
                int			             m_channels = 0;
				std::string				 m_fileName;
				std::vector<std::string> m_fileNames;
				uint32_t			     m_texture	= 0;
				bool					 m_mipmap	= true;
				ImageType				 m_type		= ImageType::RGB;
				
			public:

                static sPoint<Image> createImage(const std::string& fileName, const ImageType& imageType);
                static sPoint<Image> createImage(const std::string& fileName, const ImageType& imageType, const bool& mipmap);
                static sPoint<Image> createImage(const std::vector<std::string>& fileNames);
                static sPoint<Image> createImage(const GLuint& tid);
            
				/// <summary>
				/// Default constructor, not intended or recommended for use.
				/// </summary>
				Image() = default;

				/// <summary>
				///	Gets the width of the texture in pixels.
				/// </summary>
				/// <returns>Horizontal resolution of the texture.</returns>
				const int& getWidth() const { return m_width; }

				/// <summary>
				///	Gets the height of the texture in pixels.
				/// </summary>
				/// <returns>Vertical resolution of the texture.</returns>
				const int& getHeight() const { return m_height; }

				/// <summary>
				///	Gets the textureID of the texture.
				/// </summary>
				/// <returns>TextureID of the texture.</returns>
				const uint32_t& getTID() const { return m_texture; }

			protected:
				virtual uint32_t load() = 0;
                virtual uint32_t loadCube() = 0;
		};
    
        using MACH_IMAGE = sPoint<Image>;
	}
}
