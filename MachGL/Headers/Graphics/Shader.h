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
            /// <summary>
            /// Default constructor for a shader object, not intended for use.
            /// </summary>
            Shader() = default;

            /// <summary>
            /// Creates a shader object that contains a vertex and fragment shader.
            /// </summary>
            /// <param name="vertexPath">Filepath to the vertex shader.</param>
            /// <param name="fragmentPath">Filepath to the fragment shader.</param>
            Shader(const std::string& vertexPath, const std::string& fragmentPath);

            /// <summary>
            /// Destrustor for the shader object.
            /// </summary>
            ~Shader();

            /// <summary>
            /// Enables the shader programs.
            /// </summary>
            void enable() const;

            /// <summary>
            /// Disables the shader programs.
            /// </summary>
            void disable() const;

            /// <summary>
            /// Sets an integer to a uniform.
            /// </summary>
            /// <param name="name">Name of the uniform.</param>
            /// <param name="num">Integer value to set to the uniform.</param>
            void setUniform1i(const std::string& name, const int& num);

            /// <summary>
            /// Sets an array of integers to a uniform.
            /// </summary>
            /// <param name="name">Name of the uniform.</param>
            /// <param name="num">Array integers to be set to the uniform.</param>
            /// <param name="count">Number of values within the array.</param>
            void setUniform1iv(const std::string& name, int* num, const int& count);

            /// <summary>
            /// Sets an float to a uniform.
            /// </summary>
            /// <param name="name">Name of the uniform.</param>
            /// <param name="num">Float value to set to the uniform.</param>
            void setUniform1f(const std::string& name, const float& num);

            /// <summary>
            /// Sets a float2 to a uniform.
            /// </summary>
            /// <param name="name">Name of the uniform.</param>
            /// <param name="vec">float2 value to set to the uniform.</param>
            void setUniform2f(const std::string& name, const float2& vec);

            /// <summary>
            /// Sets a float2 to array to a uniform.
            /// </summary>
            /// <param name="name">Name of the uniform.</param>
            /// <param name="vecs">Float3 array to be set to the uniform.</param>
            /// <param name="count">Number of values within the array.</param>
            void setUniform2fv(const std::string& name, float2* vecs, const int& count);

            /// <summary>
            /// Sets a float3 to a uniform.
            /// </summary>
            /// <param name="name">Name of the uniform.</param>
            /// <param name="vec">float3 value to set to the uniform.</param>
            void setUniform3f(const std::string& name, const float3& vec);

            /// <summary>
            /// Sets a float3 to array to a uniform.
            /// </summary>
            /// <param name="name">Name of the uniform.</param>
            /// <param name="vecs">Float3 array to be set to the uniform.</param>
            /// <param name="count">Number of values within the array.</param>
            void setUniform3fv(const std::string& name, float3* vecs, const int& count);

            /// <summary>
            /// Sets a float4 to a uniform.
            /// </summary>
            /// <param name="name">Name of the uniform.</param>
            /// <param name="vec">float4 value to set to the uniform.</param>
            void setUniform4f(const std::string& name, const float4& vec);

            /// <summary>
            /// Sets a float4 to array to a uniform.
            /// </summary>
            /// <param name="name">Name of the uniform.</param>
            /// <param name="vecs">Float4 array to be set to the uniform.</param>
            /// <param name="count">Number of values within the array.</param>
            void setUniform4fv(const std::string& name, float4* vecs, const int& count);

            /// <summary>
            /// Sets a matrix4x4 to a uniform.
            /// </summary>
            /// <param name="name">Name of the uniform.</param>
            /// <param name="matrix">matrix4x4 to be set to the uniform.</param>
            void setUniformMatrix4fv(const std::string& name, const matrix4x4& matrix);

        private:
            //Loads the shaders in from the files and makes a glProgram.
            GLuint load();
        };
    }
}