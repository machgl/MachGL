/*
    
    MachGL (Alpha)
 
 */

#include "../../../Headers/API/OpenGL/OpenGLShader.h"

namespace MachGL {
    namespace Graphics {

        OpenGLShader::OpenGLShader(const std::string& vertexPath, const std::string& fragmentPath) {

            m_vertPath = vertexPath;
            m_fragPath = fragmentPath;
            m_shaderID = load();
        }
    
        uint32_t OpenGLShader::load() {
            
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
    
        void OpenGLShader::enable() const {

            if (!inCache()) {

                glUseProgram((GLuint)m_shaderID);
                ShaderInstance instance;
                instance.id = m_shaderID;
                shaderCache.push_back(instance);
            }
        }

        void OpenGLShader::disable() const {

            if (inCache()) {
                glUseProgram(0);
                
                for (uint32_t i = 0; i < shaderCache.size(); i++)
                    if (shaderCache[i].id == m_shaderID) shaderCache.erase(shaderCache.begin() + i);
            }
        }
    
        int OpenGLShader::getUniformLocation(const std::string& name) {

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
    
        OpenGLShader::~OpenGLShader() {
            
            glDeleteShader(m_shaderID);
        }
    
        void OpenGLShader::setUniform1i(const std::string& name, const GLint& num) {
            glUniform1i(getUniformLocation(name), num);
        }

        void OpenGLShader::setUniform1iv(const std::string& name, GLint* num, const GLuint& count) {
            glUniform1iv(getUniformLocation(name), count, num);
        }

        void OpenGLShader::setUniform1f(const std::string& name, const GLfloat& num) {
            glUniform1f(getUniformLocation(name), num);
        }

        void OpenGLShader::setUniform1fv(const std::string& name, GLfloat* num, const GLuint& count) {
            glUniform1fv(getUniformLocation(name), count, num);
        }

        void OpenGLShader::setUniform2f(const std::string& name, const float2& vec) {
            glUniform2f(getUniformLocation(name), vec.x, vec.y);
        }

        void OpenGLShader::setUniform2fv(const std::string& name, float2* vecs, const GLuint& count) {
            glUniform2fv(getUniformLocation(name), count, glm::value_ptr(vecs[0]));
        }

        void OpenGLShader::setUniform3f(const std::string& name, const float3& vec) {
            glUniform3f(getUniformLocation(name), vec.x, vec.y, vec.z);
        }

        void OpenGLShader::setUniform3fv(const std::string& name, float3* vecs, const GLuint& count) {
            glUniform3fv(getUniformLocation(name), count, glm::value_ptr(vecs[0]));
        }

        void OpenGLShader::setUniform4f(const std::string& name, const float4& vec) {
             glUniform4f(getUniformLocation(name), vec.x, vec.y, vec.z, vec.w);
        }

        void OpenGLShader::setUniform4fv(const std::string& name, float4* vecs, const GLuint& count) {
            glUniform3fv(getUniformLocation(name), count, glm::value_ptr(vecs[0]));
        }

        void OpenGLShader::setUniformMatrix4fv(const std::string& name, const matrix4x4& matrix) {
            glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
        }
    }
}

