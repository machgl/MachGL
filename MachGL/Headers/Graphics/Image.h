#pragma once

#include "../../Headers/Core/Includes.h"
#include "../../Vendor/stb_image.h"
#include "../../Headers/Core/DataStructures.h"

namespace MachGL {
	namespace Graphics {

		class Image {

			private:
				GLsizei m_width = 0;
				GLsizei m_height = 0;
				GLsizei m_channels = 0;
				std::string m_fileName;
				std::vector<std::string> m_fileNames;
				GLuint m_texture = 0;
				bool m_mipmap = true;
				
			public:

				Image() = default;
				Image(const std::string& fileName);
				Image(const std::string& fileName, const bool& mipmap);
				Image(const std::vector<std::string>& fileNames);
				GLuint load();
				GLuint loadCube();
				const GLsizei& getWidth() const { return m_width; }
				const GLsizei& getHeight() const { return m_height; }
				const GLuint& getTID() const { return m_texture; }
				inline sPoint<Image> ref() { return make_sPoint<Image>(*this); }
		};

	}
}