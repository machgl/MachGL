#pragma once

#include "../Core/Includes.h"
#include "../Core/DataStructures.h"
#include "../Utilities/FileUtilities.h"

namespace MachGL {
    namespace Graphics {


        class Shader {

        private:
            GLuint m_shaderID;
            const char* m_vertPath;
            const char* m_fragPath;

        public:
            Shader() = default;
            Shader(const char* vertexPath, const char* fragmentPath);
            ~Shader();

            void enable() const;
            void disable() const;
            void setUniform1i(const char* name, const int& num);
            void setUniform1iv(const char* name, int* num, const int& count);
            void setUniform1f(const char* name, const float& num);
            void setUniform2f(const char* name, const float2& vec);
            void setUniform3f(const char* name, const float3& vec);
            void setUniform3fv(const char* name, float3* vecs, const int& count);
            void setUniform4f(const char* name, const float4& vec);
            void setUniform4fv(const char* name, float4* vecs, const int& count);
            void setUniformMatrix4fv(const char* name, const matrix4x4& matrix);
        private:
            GLuint load();
        };
    }
}