#define STB_IMAGE_IMPLEMENTATION

#include "../../Headers/Graphics/Image.h"
#include "../../Headers/API/OpenGL/OpenGLImage.h"
#include "../../Headers/API/API.h"

namespace MachGL {
	namespace Graphics{

        sPoint<Image> Image::createImage(const std::string& fileName, const ImageType& imageType) {
            
            switch (GraphicsAPI::getGraphicsAPI()) {
                    
                case GraphicsAPI::API::MACH_OPEN_GL: return make_sPoint<OpenGLImage>(fileName, imageType);
                default: return make_sPoint<OpenGLImage>(fileName, imageType);
            }
        }
        
        sPoint<Image> Image::createImage(const std::string& fileName, const ImageType& imageType, const bool& mipmap) {
            
            switch (GraphicsAPI::getGraphicsAPI()) {
                    
                case GraphicsAPI::API::MACH_OPEN_GL: return make_sPoint<OpenGLImage>(fileName, imageType, mipmap);
                default: return make_sPoint<OpenGLImage>(fileName, imageType, mipmap);
            }
        }
        
        sPoint<Image> Image::createImage(const std::vector<std::string>& fileNames) {
            
            switch (GraphicsAPI::getGraphicsAPI()) {
                    
                case GraphicsAPI::API::MACH_OPEN_GL: return make_sPoint<OpenGLImage>(fileNames);
                default: return make_sPoint<OpenGLImage>(fileNames);
            }
        }
        
        sPoint<Image> Image::createImage(const GLuint& tid) {
            
            switch (GraphicsAPI::getGraphicsAPI()) {
                    
                case GraphicsAPI::API::MACH_OPEN_GL: return make_sPoint<OpenGLImage>(tid);
                default: return make_sPoint<OpenGLImage>(tid);
            }
        }
    
        std::vector<float2> Image::getAtlasUVs(const float2& coords, const float2& size) {
            
            float xOffs = (coords.x * size.x) / m_width;
            float yOffs = ((1 - coords.y) * size.y) / m_height;
            float atlasWidth = size.x / m_width;
            float atlasHeight = size.y / m_height;
            
            std::vector<float2> uvs;
            uvs.push_back(float2(xOffs, yOffs + atlasHeight));
            uvs.push_back(float2(xOffs, yOffs));
            uvs.push_back(float2(xOffs + atlasWidth, yOffs));
            uvs.push_back(float2(xOffs + atlasWidth, yOffs + atlasHeight));
            return uvs;
        }

        void Image::loadImageFromFile() {

            stbi_set_flip_vertically_on_load(true);

            if (m_type == ImageType::RGB) m_data = stbi_load(m_fileName.c_str(), &m_width, &m_height, &m_channels, STBI_rgb);
            if (m_type == ImageType::RGBA) m_data = stbi_load(m_fileName.c_str(), &m_width, &m_height, &m_channels, STBI_rgb_alpha);

            if (m_data) {

                MACH_MSG("Loaded: " + m_fileName);
            }
            else {

                MACH_ERROR_MSG("Unable to load: " + m_fileName);
                freeImage(m_data);
            }

            stbi_set_flip_vertically_on_load(false);
        }

        void Image::loadCubeFromFile() {

            uint32_t filesLoaded = 0;

            for (uint32_t i = 0; i < 6; i++) {

                m_cubeData[i] = stbi_load(m_fileNames[i].c_str(), &m_width, &m_height, &m_channels, 0);
                
                if (m_cubeData[i]) filesLoaded++;
                else {

                    MACH_ERROR_MSG("Unable to load: " + m_fileNames[i]);
                    freeImage(m_cubeData[i]);
                }
            }

            if (filesLoaded == 6) MACH_MSG("Loaded cubemap beginning: " + m_fileNames[0]);
        }

        void Image::freeImage(unsigned char* data) {

            stbi_image_free((unsigned char*)data);
        }
	}
}
