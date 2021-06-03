/*
 
    MachGL (Alpha)
 
 */

#pragma once

#include "../../Graphics/Image.h"

namespace MachGL {
    namespace Graphics {
    
        class OpenGLImage : public Image {
            
            public:
                OpenGLImage() = default;
                OpenGLImage(const std::string& fileName, const ImageType& imageType);
                OpenGLImage(const std::string& fileName, const ImageType& imageType, const bool& mipmap);
                OpenGLImage(const std::vector<std::string>& fileNames);
                OpenGLImage(const GLuint& tid);
            private:
                uint32_t load() override;
                uint32_t loadCube() override;
            
        };
    }
}
