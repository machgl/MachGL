/*
 
    MachGL (Alpha)
 
 */

#include "../../../Headers/API/OpenGL/OpenGLImage.h"

namespace MachGL {
    namespace Graphics {
    
        OpenGLImage::OpenGLImage(const std::string& fileName, const ImageType& imageType) {
            
            m_fileName = fileName;
            m_type = imageType;
            m_texture = load();
        }

        OpenGLImage::OpenGLImage(const std::string& fileName, const ImageType& imageType, const bool& mipmap) {

            m_fileName = fileName;
            m_type = imageType;
            m_mipmap = mipmap;
            m_texture = load();
        }

        OpenGLImage::OpenGLImage(const std::vector<std::string>& fileNames) {

            m_fileNames = fileNames;
            m_texture = loadCube();
        }

        OpenGLImage::OpenGLImage(const GLuint& tid) { m_texture = tid; }
    
        uint32_t OpenGLImage::load() {

            stbi_set_flip_vertically_on_load(1);

            GLuint result;
            glGenTextures(1, &result);
            glBindTexture(GL_TEXTURE_2D, result);

            unsigned char* data = nullptr;

            if (m_type == ImageType::RGB)
                data = stbi_load(m_fileName.c_str(), &m_width, &m_height, &m_channels, STBI_rgb);

            if (m_type == ImageType::RGBA)
                data = stbi_load(m_fileName.c_str(), &m_width, &m_height, &m_channels, STBI_rgb_alpha);

            if (data) {

                if (m_type == ImageType::RGB)
                    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                if (m_type == ImageType::RGBA)
                    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

                MACH_MSG("Loaded: " + m_fileName);
                stbi_image_free(data);
            }
            else {

                MACH_ERROR_MSG("Unable to load: " + m_fileName);
                stbi_image_free(data);
            }
            
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

            if (m_mipmap) {

                glGenerateMipmap(GL_TEXTURE_2D);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
                glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, 0);
            }
            else {

                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            }

            GLfloat value, maxAnisotropy = 8.0f;
            
            #if defined(MACH_PLATFORM_WINDOWS)
                if (glfwExtensionSupported("GL_ARB_texture_filter_anisotropic")) {
                
                    glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY, &value);
                    value = (value > maxAnisotropy) ? maxAnisotropy : value;
                    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY, value);
                }
            #endif
        
            glBindTexture(GL_TEXTURE_2D, 0);
            stbi_set_flip_vertically_on_load(0);
            return result;
        }
    
        uint32_t OpenGLImage::loadCube() {

            GLuint result;
            glGenTextures(1, &result);
            glBindTexture(GL_TEXTURE_CUBE_MAP, result);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

            for (uint32_t i = 0; i < m_fileNames.size(); i++) {

                unsigned char* data = stbi_load(m_fileNames[i].c_str(), &m_width, &m_height, &m_channels, 0);

                if (data) {

                    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB,
                        m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                    stbi_image_free(data);
                }
                else {

                    MACH_ERROR_MSG("Unable to load: " + m_fileNames[i]);
                    stbi_image_free(data);
                }
            }
            
            glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
            return result;
        }
    }
}
