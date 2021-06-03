/*
    
    MachGL (Alpha)
 
 */

#pragma once

#include "../../Core/Includes.h"
#include "../../Core/DataStructures.h"
#include "../../Graphics/Shader.h"

namespace MachGL {
    namespace Graphics {

        class OpenGLShader : public Shader {
            
            public:
                OpenGLShader(const std::string& vertexPath, const std::string& fragmentPath);
            
                ~OpenGLShader();

                void enable() const override;
                void disable() const override;
                void setUniform1i(const std::string& name, const GLint& num) override;
                void setUniform1iv(const std::string& name, GLint* num, const GLuint& count) override;
                void setUniform1f(const std::string& name, const GLfloat& num) override;
                void setUniform1fv(const std::string& name, GLfloat* num, const GLuint& count) override;
                void setUniform2f(const std::string& name, const float2& vec) override;
                void setUniform2fv(const std::string& name, float2* vecs, const GLuint& count) override;
                void setUniform3f(const std::string& name, const float3& vec) override;
                void setUniform3fv(const std::string& name, float3* vecs, const GLuint& count) override;
                void setUniform4f(const std::string& name, const float4& vec) override;
                void setUniform4fv(const std::string& name, float4* vecs, const GLuint& count) override;
                void setUniformMatrix4fv(const std::string& name, const matrix4x4& matrix) override;

        private:
            //Loads the shaders in from the files and makes a glProgram.
            uint32_t load() override;
            int getUniformLocation(const std::string& name) override;
        };
    }
}
