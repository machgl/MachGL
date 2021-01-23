#define STB_IMAGE_IMPLEMENTATION
#include "Image.h"


namespace MachGL {
	namespace Graphics{

		Image::Image(const char* fileName) : m_fileName(fileName) {

			m_texture = load();
		}

		Image::Image(std::vector<const char*> fileNames) : m_fileNames(fileNames) {

			m_texture = loadCube();
		}

		GLuint Image::load() {

			stbi_set_flip_vertically_on_load(1);

			GLuint result;
			glGenTextures(1, &result);
			glBindTexture(GL_TEXTURE_2D, result);

			unsigned char* data = stbi_load(m_fileName, &m_width, &m_height, &m_channels, 0);
			
			if (data) {

				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				stbi_image_free(data);
			}
			else {

				std::cout << "Unable to load: " << m_fileName << std::endl;
				stbi_image_free(data);
			}

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glGenerateMipmap(GL_TEXTURE_2D);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, 0);

			GLfloat value, maxAnisotropy = 8.0f;
			if (glfwExtensionSupported("GL_ARB_texture_filter_anisotropic")) {

				glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY, &value);
				value = (value > maxAnisotropy) ? maxAnisotropy : value;
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY, value);
			}
		
			glBindTexture(GL_TEXTURE_2D, 0);
			return result;
		}

		GLuint Image::loadCube() {


			GLuint result;
			glGenTextures(1, &result);
			glBindTexture(GL_TEXTURE_CUBE_MAP, result);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	
			for (int i = 0; i < m_fileNames.size(); i++) {

				unsigned char* data = stbi_load(m_fileNames[i], &m_width, &m_height, &m_channels, 0);

				if (data) {

					glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, 
						m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
					stbi_image_free(data);
				}
				else {

					std::cout << "Unable to load: " << m_fileNames[i] << std::endl;
					stbi_image_free(data);
				}
			}
			
			glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
			return result;
		}
	}
}