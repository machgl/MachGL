#define STB_IMAGE_IMPLEMENTATION

#include "../../Headers/Graphics/Image.h"
#include "../../Headers/API/OpenGL/OpenGLImage.h"

namespace MachGL {
	namespace Graphics{

        sPoint<Image> Image::createImage(const std::string& fileName, const ImageType& imageType) {
            
            switch (MACH_GRAPHICS_API) {
                    
                case GraphicsAPI::MACH_OpenGL: return make_sPoint<OpenGLImage>(fileName, imageType);
                default: return make_sPoint<OpenGLImage>(fileName, imageType);
            }
        }
        
        sPoint<Image> Image::createImage(const std::string& fileName, const ImageType& imageType, const bool& mipmap) {
            
            switch (MACH_GRAPHICS_API) {
                    
                case GraphicsAPI::MACH_OpenGL: return make_sPoint<OpenGLImage>(fileName, imageType, mipmap);
                default: return make_sPoint<OpenGLImage>(fileName, imageType, mipmap);
            }
        }
        
        sPoint<Image> Image::createImage(const std::vector<std::string>& fileNames) {
            
            switch (MACH_GRAPHICS_API) {
                    
                case GraphicsAPI::MACH_OpenGL: return make_sPoint<OpenGLImage>(fileNames);
                default: return make_sPoint<OpenGLImage>(fileNames);
            }
        }
        
        sPoint<Image> Image::createImage(const GLuint& tid) {
            
            switch (MACH_GRAPHICS_API) {
                    
                case GraphicsAPI::MACH_OpenGL: return make_sPoint<OpenGLImage>(tid);
                default: return make_sPoint<OpenGLImage>(tid);
            }
        }
	}
}
