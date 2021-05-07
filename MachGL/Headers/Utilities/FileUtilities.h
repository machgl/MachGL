#pragma once

#include "../Core/Includes.h"

namespace MachGL {
	namespace Utilities {

        class FileUtilities {

            public:
                static std::string fileToString(const std::string& filePath) {

                    std::string   result;
                    std::ifstream in(filePath, std::ios::in | std::ios::binary);

                    if (in) {
                        in.seekg(0, std::ios::end);
                        size_t size = in.tellg();
                        if (size != -1) {

                            result.resize(size);
                            in.seekg(0, std::ios::beg);
                            in.read(&result[0], size);

                            MACH_MSG("Loaded: " + filePath);
                        }
                        else MACH_ERROR_MSG("Failed to read from the file: " + filePath);
                    }
                    else MACH_ERROR_MSG("Could not open the file: " + filePath);
                    return result;
                }

                static void tokenize(std::string const& str, const char& delim, std::vector<std::string>& out) {

                    size_t start;
                    size_t end = 0;

                    while ((start = str.find_first_not_of(delim, end)) != std::string::npos) {

                        end = str.find(delim, start);
                        out.push_back(str.substr(start, end - start));
                    }
                }
        };
	}
}