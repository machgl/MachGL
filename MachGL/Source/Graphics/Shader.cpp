#include "../../Headers/Graphics/Shader.h"

namespace MachGL {
    namespace Graphics {

        Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {

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

        void Shader::setUniform1i(const std::string& name, const int& num) {
            glUniform1i(glGetUniformLocation(m_shaderID, name.c_str()), num);
        }

        void Shader::setUniform1iv(const std::string& name, int* num, const int& count) {
            glUniform1iv(glGetUniformLocation(m_shaderID, name.c_str()), count, num);
        }

        void Shader::setUniform1f(const std::string& name, const float& num) {
            glUniform1f(glGetUniformLocation(m_shaderID, name.c_str()), num);
        }

        void Shader::setUniform2f(const std::string& name, const float2& vec) {
            glUniform2f(glGetUniformLocation(m_shaderID, name.c_str()), vec.x, vec.y);
        }

        void Shader::setUniform2fv(const std::string& name, float2* vecs, const int& count) {
            glUniform2fv(glGetUniformLocation(m_shaderID, name.c_str()), count, glm::value_ptr(vecs[0]));
        }

        void Shader::setUniform3f(const std::string& name, const float3& vec) {
            glUniform3f(glGetUniformLocation(m_shaderID, name.c_str()), vec.x, vec.y, vec.z);
        }

        void Shader::setUniform3fv(const std::string& name, float3* vecs, const int& count) {
            glUniform3fv(glGetUniformLocation(m_shaderID, name.c_str()), count, glm::value_ptr(vecs[0]));
        }

        void Shader::setUniform4f(const std::string& name, const float4& vec) {
            glUniform4f(glGetUniformLocation(m_shaderID, name.c_str()), vec.x, vec.y, vec.z, vec.w);
        }

        void Shader::setUniform4fv(const std::string& name, float4* vecs, const int& count) {
            glUniform3fv(glGetUniformLocation(m_shaderID, name.c_str()), count, glm::value_ptr(vecs[0]));
        }

        void Shader::setUniformMatrix4fv(const std::string& name, const matrix4x4& matrix) {
            glUniformMatrix4fv(glGetUniformLocation(m_shaderID, name.c_str()), 1, GL_FALSE, &matrix[0][0]);
        }
    }
}