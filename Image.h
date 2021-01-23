#pragma once

#include "Includes.h"
#include "stb_image.h"

namespace MachGL {
	namespace Graphics {

		class Image {

			private:
				GLsizei m_width = 0;
				GLsizei m_height = 0;
				GLsizei m_channels = 0;
				const char* m_fileName;
				std::vector<const char*> m_fileNames;
				GLuint m_texture = 0;
				
			public:

				Image() = default;
				Image(const char* fileName);
				Image(std::vector<const char*> fileNames);
				GLuint load();
				GLuint loadCube();
				const GLsizei& getWidth() const { return m_width; }
				const GLsizei& getHeight() const { return m_height; }
				const GLuint& getTID() const { return m_texture; }
		};
	}
}