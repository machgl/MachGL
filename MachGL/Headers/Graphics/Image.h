#pragma once

#include "../Core/Includes.h"
#include "../../Vendor/stb_image.h"
#include "../Core/DataStructures.h"

namespace MachGL {
	namespace Graphics {

		enum class ImageType {

			RGB, RGBA
		};

		class Image {

			private:
				GLsizei m_width = 0;
				GLsizei m_height = 0;
				GLsizei m_channels = 0;
				std::string m_fileName;
				std::vector<std::string> m_fileNames;
				GLuint m_texture = 0;
				bool m_mipmap = true;
				ImageType m_type = ImageType::RGB;
				
			public:

				/// <summary>
				/// Default constructor, not intended or recommended for use.
				/// </summary>
				Image() = default;

				/// <summary>
				/// Creates a texture from a file.
				/// <param name="fileName">File path to where the imgage is sored.</param>
				/// <param name="imageType">Determines the image channels. RGB or RGBA.</param>
				/// </summary>
				Image(const std::string& fileName, const ImageType& imageType);

				/// <summary>
				/// Creates a texture from a file.
				/// <param name="fileName">File path to where the imgage is sored.</param>
				/// <param name="imageType">Determines the image channels. RGB or RGBA.</param>
				/// <param name="mipmap">Determines if the texture can be subject ti mipmapping.</param>
				/// </summary>
				Image(const std::string& fileName, const ImageType& imageType, const bool& mipmap);

				/// <summary> 
				/// Takes a list of images to load into a cubemap.
				/// <param name="fileNames">List of file paths to load into a cubemap.</param>
				/// </summary>
				Image(const std::vector<std::string>& fileNames);

				/// <summary>
				///	Makes a texture object from a textureID.
				/// <param name="tid">TextureID to make into image object.</param> 
				/// </summary>
				Image(const GLuint& tid);

				/// <summary>
				///	Gets the width of the texture in pixels.
				/// <returns>Horizontal resolution of the texture.</returns>
				/// </summary>
				const GLsizei& getWidth() const { return m_width; }

				/// <summary>
				///	Gets the height of the texture in pixels.
				/// <returns>Vertical resolution of the texture.</returns>
				/// </summary>
				const GLsizei& getHeight() const { return m_height; }

				/// <summary>
				///	Gets the textureID of the texture.
				/// <returns>TextureID of the texture.</returns>
				/// </summary>
				const GLuint& getTID() const { return m_texture; }

				/// <summary>
				///	Gets the reference of the image object as a shared pointer (replaces &).
				/// <returns>Reference of the image object.</returns>
				/// </summary>
				inline sPoint<Image> ref() { return make_sPoint<Image>(*this); }

			private: 
				GLuint load();
				GLuint loadCube();
		};
	}
}