/*
 
    MachGL (Alpha)
 
 */

#pragma once

#include "MachPCH.h"
#include "../Core/DataStructures.h"
#include "../Utilities/FileUtilities.h"

namespace MachGL {
    namespace Graphics {

        enum class SupportedShaders {

            VERTEX, FRAGMENT, NON
        };

        static std::string m_cacheDirectory = "Cache/";
        
        class Shader {

            protected:
                uint32_t                                     m_shaderID;
                std::string                                  m_vertPath;
                std::string                                  m_fragPath;
                std::string                                  m_shaderPath;
                std::string                                  m_fileName;
                std::unordered_map<std::string, uint32_t>    m_uniformLocations;
                std::unordered_map<SupportedShaders, std::string> m_shaders;
                std::unordered_map<SupportedShaders, std::vector<uint32_t>> m_vulkanShaders;
                std::unordered_map<SupportedShaders, std::vector<uint32_t>> m_OpenGLShaders;
                std::unordered_map<SupportedShaders, std::string> m_OpenGLSource;
                
            public:
                static sPoint<Shader> createShader(const std::string& vertexPath, const std::string& fragmentPath);
                static sPoint<Shader> createShader(const std::string& shaderPath);
                
                /// <summary>
                /// Default constructor for a shader object, not intended for use.
                /// </summary>
                Shader() = default;

                /// <summary>
                /// Destrustor for the shader object.
                /// </summary>
                ~Shader() = default;

                /// <summary>
                /// Enables the shader programs.
                /// </summary>
                virtual void enable() const = 0;

                /// <summary>
                /// Disables the shader programs.
                /// </summary>
                virtual void disable() const = 0;

                /// <summary>
                /// Sets an integer to a uniform.
                /// </summary>
                /// <param name="name">Name of the uniform.</param>
                /// <param name="num">Integer value to set to the uniform.</param>
                virtual void setUniform1i(const std::string& name, const GLint& num) = 0;

                /// <summary>
                /// Sets an array of integers to a uniform.
                /// </summary>
                /// <param name="name">Name of the uniform.</param>
                /// <param name="num">Array integers to be set to the uniform.</param>
                /// <param name="count">Number of values within the array.</param>
                virtual void setUniform1iv(const std::string& name, GLint* num, const GLuint& count) = 0;

                /// <summary>
                /// Sets an float to a uniform.
                /// </summary>
                /// <param name="name">Name of the uniform.</param>
                /// <param name="num">Float value to set to the uniform.</param>
                virtual void setUniform1f(const std::string& name, const GLfloat& num) = 0;

                virtual void setUniform1fv(const std::string& name, GLfloat* num, const GLuint& count) = 0;

                /// <summary>
                /// Sets a float2 to a uniform.
                /// </summary>
                /// <param name="name">Name of the uniform.</param>
                /// <param name="vec">float2 value to set to the uniform.</param>
                virtual void setUniform2f(const std::string& name, const float2& vec) = 0;

                /// <summary>
                /// Sets a float2 to array to a uniform.
                /// </summary>
                /// <param name="name">Name of the uniform.</param>
                /// <param name="vecs">Float3 array to be set to the uniform.</param>
                /// <param name="count">Number of values within the array.</param>
                virtual void setUniform2fv(const std::string& name, float2* vecs, const GLuint& count) = 0;

                /// <summary>
                /// Sets a float3 to a uniform.
                /// </summary>
                /// <param name="name">Name of the uniform.</param>
                /// <param name="vec">float3 value to set to the uniform.</param>
                virtual void setUniform3f(const std::string& name, const float3& vec) = 0;

                /// <summary>
                /// Sets a float3 to array to a uniform.
                /// </summary>
                /// <param name="name">Name of the uniform.</param>
                /// <param name="vecs">Float3 array to be set to the uniform.</param>
                /// <param name="count">Number of values within the array.</param>
                virtual void setUniform3fv(const std::string& name, float3* vecs, const GLuint& count) = 0;

                /// <summary>
                /// Sets a float4 to a uniform.
                /// </summary>
                /// <param name="name">Name of the uniform.</param>
                /// <param name="vec">float4 value to set to the uniform.</param>
                virtual void setUniform4f(const std::string& name, const float4& vec) = 0;

                /// <summary>
                /// Sets a float4 to array to a uniform.
                /// </summary>
                /// <param name="name">Name of the uniform.</param>
                /// <param name="vecs">Float4 array to be set to the uniform.</param>
                /// <param name="count">Number of values within the array.</param>
                virtual void setUniform4fv(const std::string& name, float4* vecs, const GLuint& count) = 0;

                /// <summary>
                /// Sets a matrix4x4 to a uniform.
                /// </summary>
                /// <param name="name">Name of the uniform.</param>
                /// <param name="matrix">matrix4x4 to be set to the uniform.</param>
                virtual void setUniformMatrix4fv(const std::string& name, const matrix4x4& matrix) = 0;

                inline const uint32_t& getShaderID() const { return m_shaderID; }

            protected:
                virtual uint32_t load() = 0;
                virtual int getUniformLocation(const std::string& name) = 0;
                bool inCache() const;
                std::unordered_map<SupportedShaders, std::string> splitShader(const std::string & shaderPath);
                virtual void createCacheDirectory() = 0;
                void compileVulkanBinaries(const std::unordered_map<SupportedShaders, std::string>& shaders);
                void compileOpenGLBinaries(const std::unordered_map<SupportedShaders, std::string>& shaders);
                virtual void createProgramFromBinaries() = 0;
                shaderc_shader_kind getSupportedShaderVulkan(const SupportedShaders& shader);
                shaderc_shader_kind getSupportedShaderOpenGL(const SupportedShaders& shader);
                GLenum getOpenGLShaderType(const SupportedShaders& shader);
        };
    
        using MACH_SHADER = sPoint<Shader>;
        using MACH_RAW_SHADERS = std::unordered_map<SupportedShaders, std::string>;
        using MACH_COMPILED_SHADERS = std::unordered_map<SupportedShaders, std::vector<uint32_t>>;
    }
}
