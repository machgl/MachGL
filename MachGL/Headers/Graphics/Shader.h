#pragma once

#include "../Core/Includes.h"
#include "../Core/DataStructures.h"
#include "../Utilities/FileUtilities.h"

namespace MachGL {
    namespace Graphics {

        class Shader {

        private:
            GLuint m_shaderID;
            std::string m_vertPath;
            std::string m_fragPath;

        public:
            Shader() = default;
            Shader(const std::string& vertexPath, const std::string& fragmentPath);
            ~Shader();

            void enable() const;
            void disable() const;
            void setUniform1i(const std::string& name, const int& num);
            void setUniform1iv(const std::string& name, int* num, const int& count);
            void setUniform1f(const std::string& name, const float& num);
            void setUniform2f(const std::string& name, const float2& vec);
            void setUniform3f(const std::string& name, const float3& vec);
            void setUniform3fv(const std::string& name, float3* vecs, const int& count);
            void setUniform4f(const std::string& name, const float4& vec);
            void setUniform4fv(const std::string& name, float4* vecs, const int& count);
            void setUniformMatrix4fv(const std::string& name, const matrix4x4& matrix);

        private:
            GLuint load();
        };
    }
}