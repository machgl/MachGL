#include "../../Headers/Graphics/Shader.h"

namespace MachGL {
    namespace Graphics {

        Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {

            m_vertPath = vertexPath;
            m_fragPath = fragmentPath;
            m_shaderID = load();
        }

        GLuint Shader::load() {

            GLuint program  = glCreateProgram();
            GLuint vertex   = glCreateShader(GL_VERTEX_SHADER);
            GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
            GLint  result;

            std::string vertSourceString = Utilities::FileUtilities::fileToString(m_vertPath);
            std::string fragSourceString = Utilities::FileUtilities::fileToString(m_fragPath);

            const char* vertSource = vertSourceString.c_str();
            const char* fragSource = fragSourceString.c_str();

            glShaderSource(vertex, 1, &vertSource, 0);
            glCompileShader(vertex);
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

            glShaderSource(fragment, 1, &fragSource, 0);
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

        bool Shader::inCache() const {

            if (shaderCache.size() > 0)
                for (uint32_t i = 0; i < shaderCache.size(); i++) if (shaderCache[i].id == m_shaderID) return true;

            return false;
        }

        void Shader::enable() const {

            if (!inCache()) {

                glUseProgram(m_shaderID);
                ShaderInstance instance;
                instance.id = m_shaderID;
                shaderCache.push_back(instance);
            }
        }

        void Shader::disable() const {

            if (inCache()) {
                glUseProgram(0);
                
                for (uint32_t i = 0; i < shaderCache.size(); i++)
                    if (shaderCache[i].id == m_shaderID) shaderCache.erase(shaderCache.begin() + i);
            }
        }

        GLint Shader::getUniformLocation(const std::string& name) {

            if (m_uniformLocations.find(name) != m_uniformLocations.end())
                return m_uniformLocations[name];

            GLint location = glGetUniformLocation(m_shaderID, name.c_str());

            if (location != -1) {

                m_uniformLocations[name] = location;
                return location;

            } else{
                
                MACH_ERROR_MSG("Uniform " + name + " not found");
                return 0;
            }
        }

        void Shader::setUniform1i(const std::string& name, const GLint& num) {
            glUniform1i(getUniformLocation(name), num);
        }

        void Shader::setUniform1iv(const std::string& name, GLint* num, const GLuint& count) {
            glUniform1iv(getUniformLocation(name), count, num);
        }

        void Shader::setUniform1f(const std::string& name, const GLfloat& num) {
            glUniform1f(getUniformLocation(name), num);
        }

        void Shader::setUniform1fv(const std::string& name, GLfloat* num, const GLuint& count) {
            glUniform1fv(getUniformLocation(name), count, num);
        }

        void Shader::setUniform2f(const std::string& name, const float2& vec) {
            glUniform2f(getUniformLocation(name), vec.x, vec.y);
        }

        void Shader::setUniform2fv(const std::string& name, float2* vecs, const GLuint& count) {
            glUniform2fv(getUniformLocation(name), count, glm::value_ptr(vecs[0]));
        }

        void Shader::setUniform3f(const std::string& name, const float3& vec) {
            glUniform3f(getUniformLocation(name), vec.x, vec.y, vec.z);
        }

        void Shader::setUniform3fv(const std::string& name, float3* vecs, const GLuint& count) {
            glUniform3fv(getUniformLocation(name), count, glm::value_ptr(vecs[0]));
        }

        void Shader::setUniform4f(const std::string& name, const float4& vec) {
             glUniform4f(getUniformLocation(name), vec.x, vec.y, vec.z, vec.w);
        }

        void Shader::setUniform4fv(const std::string& name, float4* vecs, const GLuint& count) {
            glUniform3fv(getUniformLocation(name), count, glm::value_ptr(vecs[0]));
        }

        void Shader::setUniformMatrix4fv(const std::string& name, const matrix4x4& matrix) {
            glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
        }
    }
}