#include "../../Headers/Graphics/Shader.h"

namespace MachGL {
    namespace Graphics {

        Shader::Shader(const char* vertexPath, const char* fragmentPath) {

            m_vertPath = vertexPath;
            m_fragPath = fragmentPath;
            m_shaderID = load();
        }

        Shader::~Shader() {

            glDeleteProgram(m_shaderID);
        }

        GLuint Shader::load() {

            GLuint program = glCreateProgram();
            GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
            GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

            std::string vertSourceString = Utilities::readFromFile(m_vertPath);
            std::string fragSourceString = Utilities::readFromFile(m_fragPath);

            const char* vertSource = vertSourceString.c_str();
            const char* fragSource = fragSourceString.c_str();

            glShaderSource(vertex, 1, &vertSource, NULL);
            glCompileShader(vertex);

            GLint result;
            glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);

            if (result == GL_FALSE) {

                GLint length;
                glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
                std::vector<char> error(length);
                glGetShaderInfoLog(vertex, length, &length, &error[0]);
                std::cout << "\nVertex: " << &error[0] << std::endl;
                glDeleteShader(vertex);
                return 0;
            }

            glShaderSource(fragment, 1, &fragSource, NULL);
            glCompileShader(fragment);

            glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);

            if (result == GL_FALSE) {

                GLint length;
                glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
                std::vector<char> error(length);
                glGetShaderInfoLog(fragment, length, &length, &error[0]);
                std::cout << "\nFragment: " << &error[0] << std::endl;
                glDeleteShader(fragment);
                return 0;
            }

            glAttachShader(program, vertex);
            glAttachShader(program, fragment);

            glLinkProgram(program);
            glValidateProgram(program);

            glDeleteShader(vertex);
            glDeleteShader(fragment);

            return program;
        }

        void Shader::enable() const {

            glUseProgram(m_shaderID);
        }

        void Shader::disable() const {

            glUseProgram(0);
        }

        void Shader::setUniform1i(const char* name, const int& num) {
            glUniform1i(glGetUniformLocation(m_shaderID, name), num);
        }

        void Shader::setUniform1iv(const char* name, int* num, const int& count) {
            glUniform1iv(glGetUniformLocation(m_shaderID, name), count, num);
        }

        void Shader::setUniform1f(const char* name, const float& num) {
            glUniform1f(glGetUniformLocation(m_shaderID, name), num);
        }

        void Shader::setUniform2f(const char* name, const float2& vec) {
            glUniform2f(glGetUniformLocation(m_shaderID, name), vec.x, vec.y);
        }

        void Shader::setUniform3f(const char* name, const float3& vec) {
            glUniform3f(glGetUniformLocation(m_shaderID, name), vec.x, vec.y, vec.z);
        }

        void Shader::setUniform3fv(const char* name, float3* vecs, const int& count) {
            glUniform3fv(glGetUniformLocation(m_shaderID, name), count, glm::value_ptr(vecs[0]));
        }

        void Shader::setUniform4f(const char* name, const float4& vec) {
            glUniform4f(glGetUniformLocation(m_shaderID, name), vec.x, vec.y, vec.z, vec.w);
        }

        void Shader::setUniform4fv(const char* name, float4* vecs, const int& count) {
            glUniform3fv(glGetUniformLocation(m_shaderID, name), count, glm::value_ptr(vecs[0]));
        }

        void Shader::setUniformMatrix4fv(const char* name, const matrix4x4& matrix) {
            glUniformMatrix4fv(glGetUniformLocation(m_shaderID, name), 1, GL_FALSE, &matrix[0][0]);
        }
    }
}