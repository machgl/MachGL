/*
    
    MachGL (Alpha)
 
 */

#include "../../../Headers/API/OpenGL/OpenGLShader.h"
#include "../../../Headers/Core/Cache.h"

namespace MachGL {
    namespace Graphics {

        OpenGLShader::OpenGLShader(const std::string& vertexPath, const std::string& fragmentPath) {

            m_vertPath = vertexPath;
            m_fragPath = fragmentPath;
            m_shaderID = load();
        }

        OpenGLShader::OpenGLShader(const std::string& shaderPath) {

            m_shaderPath = shaderPath;
            m_shaderID = load();
        }

        uint32_t OpenGLShader::load() {
            
            GLuint program  = glCreateProgram();
            GLint  result;

            std::unordered_map<SupportedShaders, std::string> shaders;
            
            if (m_shaderPath != "") {

                shaders = splitShader(m_shaderPath);
            }
            else {

                shaders[SupportedShaders::VERTEX] = Utilities::FileUtilities::fileToString(m_vertPath);
                shaders[SupportedShaders::FRAGMENT] = Utilities::FileUtilities::fileToString(m_fragPath);
            }

            for (auto i = shaders.begin(); i != shaders.end(); i++) {

                uint32_t shader;
                std::string shaderType = "";

                switch (i->first) {

                    case SupportedShaders::VERTEX:
                        shader = glCreateShader(GL_VERTEX_SHADER);
                        shaderType = "Vertex";
                        break;
                    case SupportedShaders::FRAGMENT:
                        shader = glCreateShader(GL_FRAGMENT_SHADER);
                        shaderType = "Fragment";
                        break;
                    default:
                        shader = -1;
                        shaderType = "Unknown";
                        return -1;
                        break;
                }

                const char* source = i->second.c_str();

                glShaderSource(shader, 1, &source, 0);
                glCompileShader(shader);
                glGetShaderiv(shader, GL_COMPILE_STATUS, &result);

                if (result == GL_FALSE) {

                    GLint length;
                    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
                    std::vector<char> error(length);
                    glGetShaderInfoLog(shader, length, &length, &error[0]);
                    std::cout << "\n" << shaderType << " " << &error[0] << std::endl;
                    glDeleteShader(shader);
                    return 0;
                }

                glAttachShader(program, shader);
            }

            glLinkProgram(program);
            glValidateProgram(program);

            return program;
        }

        void OpenGLShader::createProgramFromBinaries() {

            uint32_t shaderID = glCreateProgram();
            std::vector<uint32_t> uniqueIDs;

            for (auto&& [shader, spirv] : m_OpenGLShaders) {

                uint32_t uniqueID = uniqueIDs.emplace_back(glCreateShader(getOpenGLShaderType(shader)));
                glShaderBinary(1, &uniqueID, GL_SHADER_BINARY_FORMAT_SPIR_V, spirv.data(), spirv.size() * sizeof(uint32_t));
                glSpecializeShader(uniqueID, "main", 0, nullptr, nullptr);
                glAttachShader(shaderID, uniqueID);
            }

            glLinkProgram(shaderID);
            GLint isLinked;
            glGetProgramiv(shaderID, GL_LINK_STATUS, &isLinked);

            if (isLinked == GL_FALSE) {

                GLint maxLength;
                glGetProgramiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);

                std::vector<GLchar> infoLog(maxLength);
                glGetProgramInfoLog(shaderID, maxLength, &maxLength, infoLog.data());

                glDeleteProgram(shaderID);

                for (auto id : uniqueIDs) {

                    glDeleteShader(id);
                }
            }

            for (auto id : uniqueIDs) {

                glDetachShader(shaderID, id);
                glDeleteShader(id);
            }

            m_shaderID = shaderID;
        }
    
        void OpenGLShader::enable() const {

            if (!inCache()) {

                glUseProgram((GLuint)m_shaderID);
                Cache::pushToCache(CachedInstance(m_shaderID));
            }
        }

        void OpenGLShader::disable() const {

            if (inCache()) {

                glUseProgram(0);
                Cache::eraseFromCache(m_shaderID);
            }
            else {

                MACH_WARN_MSG("Shader: " + m_shaderPath + " was disabled more than once concurrently");
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
        
        void OpenGLShader::createCacheDirectory() {

            std::string cacheDirectory = m_cacheDirectory + "OpenGL";
            
            if (!std::filesystem::exists(cacheDirectory))
                std::filesystem::create_directories(cacheDirectory);
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

