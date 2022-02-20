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

            GLuint result;

            glCreateTextures(GL_TEXTURE_2D, 1, &result);

            glGenTextures(1, &result);
            glBindTexture(GL_TEXTURE_2D, result);

            loadImageFromFile();

            if (m_data) {

                if (m_type == ImageType::RGB)
                    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_data);
                if (m_type == ImageType::RGBA)
                    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_data);
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
            
            #if defined(MACH_PLATFORM_WINDOWS)
                GLfloat value, maxAnisotropy = 8.0f;
                if (glfwExtensionSupported("GL_ARB_texture_filter_anisotropic")) {
                
                    glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY, &value);
                    value = (value > maxAnisotropy) ? maxAnisotropy : value;
                    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY, value);
                }
            #endif
        
            glBindTexture(GL_TEXTURE_2D, 0);
            freeImage(m_data);
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

            loadCubeFromFile();

            for (uint32_t i = 0; i < 6; i++) {

                if (m_cubeData[i]) {

                    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB,
                        m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_cubeData[i]);
                    freeImage(m_cubeData[i]);
                }
            }
            
            glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
            return result;
        }
    }
}
