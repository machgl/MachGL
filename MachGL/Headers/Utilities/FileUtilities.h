#pragma once

#include "../../Headers/Core/Includes.h"

namespace MachGL {
	namespace Utilities {

        static std::string readFromFile(const char* filePath) {

            FILE* file;

            #if defined(__WIN32__) || defined(__WIN64__)
                errno_t error;
                if ((error = fopen_s(&file, filePath, "rt")) != 0) 
                    std::cout << "Failed to open file" << std::endl;
            #else
                file = fopen(filePath, "rt");
            #endif

            if (file == NULL) {

                std::cout << "Failed to open file" << std::endl;
            }
            else {

                fseek(file, 0, SEEK_END);
                unsigned long length = ftell(file);
                char* data = new char[length + 1];
                memset(data, 0, length + 1);
                fseek(file, 0, SEEK_SET);
                fread(data, 1, length, file);
                fclose(file);
                std::string result(data);
                delete[] data;
                return result;
            }
        }
	}
}