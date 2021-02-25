#pragma once

#include "../Core/Includes.h"

namespace MachGL {
	namespace Utilities {

        static std::string readFromFile(const std::string& filePath) {

            std::string result;
            std::ifstream in(filePath, std::ios::in | std::ios::binary);

            if (in) {
                in.seekg(0, std::ios::end);
                size_t size = in.tellg();
                if (size != -1) {

                    result.resize(size);
                    in.seekg(0, std::ios::beg);
                    in.read(&result[0], size);
                }
                else {
                    MACH_ERROR_MSG("Failed to read from the file");
                }
            }
            else {
                MACH_ERROR_MSG("Could not open the file");
            }

            return result;
        }
	}
}