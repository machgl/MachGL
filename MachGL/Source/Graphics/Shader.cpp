/*

Mach::GL (Alpha)

*/

#include "../../Headers/Graphics/Shader.h"
#include "../../Headers/API/OpenGL/OpenGLShader.h"
#include "../../Headers/API/API.h"
#include "../../Headers/Core/Cache.h"

namespace MachGL {
    namespace Graphics {

        MACH_SHADER Shader::createShader(const std::string& vertexPath, const std::string& fragmentPath) {
            
            switch (GraphicsAPI::getGraphicsAPI()) {

                case GraphicsAPI::API::MACH_OPEN_GL: return make_sPoint<OpenGLShader>(vertexPath, fragmentPath);
                default: return make_sPoint<OpenGLShader>(vertexPath, fragmentPath);
            }
        }

        MACH_SHADER Shader::createShader(const std::string& shaderPath) {

            switch (GraphicsAPI::getGraphicsAPI()) {

                case GraphicsAPI::API::MACH_OPEN_GL: return make_sPoint<OpenGLShader>(shaderPath);
                default: return make_sPoint<OpenGLShader>(shaderPath);
            }
        }
        
        bool Shader::inCache() const {  return Cache::checkInCache(m_shaderID); }

        shaderc_shader_kind Shader::getSupportedShaderVulkan(const SupportedShaders& shader) {

            switch (shader) {

                case SupportedShaders::VERTEX: return shaderc_vertex_shader;
                case SupportedShaders::FRAGMENT: return shaderc_fragment_shader;
                default: return shaderc_vertex_shader;
            }
        }

        shaderc_shader_kind Shader::getSupportedShaderOpenGL(const SupportedShaders& shader) {

            switch (shader) {

                case SupportedShaders::VERTEX: return shaderc_glsl_vertex_shader;
                case SupportedShaders::FRAGMENT: return shaderc_glsl_fragment_shader;
                default: return shaderc_glsl_vertex_shader;
            }
        }

        GLenum Shader::getOpenGLShaderType(const SupportedShaders& shader) {

            switch (shader) {

                case SupportedShaders::VERTEX: return GL_VERTEX_SHADER;
                case SupportedShaders::FRAGMENT: return GL_FRAGMENT_SHADER;
                default: return GL_VERTEX_SHADER;
            }
        }

        MACH_RAW_SHADERS Shader::splitShader(const std::string& shaderPath) {

            size_t lastSlash = shaderPath.find_last_of("/\\");
            size_t lastDot = shaderPath.find_last_of(".");

            if (shaderPath.substr(lastDot + 1) != "mglsdr" || lastDot == std::string::npos) {

                MACH_ERROR_MSG("Combined shader file requires the extension .mglsdr");
                return std::unordered_map<SupportedShaders, std::string>();
            }

            if (lastSlash == std::string::npos)
                m_fileName = shaderPath.substr(0, lastDot);
            else {

                std::string tmp = shaderPath.substr(lastSlash + 1);
                m_fileName = tmp.substr(0, tmp.find_last_of("."));
            }

            MACH_RAW_SHADERS shaders;
            SupportedShaders currentShader = SupportedShaders::NON;
            std::fstream shaderFile;
            
            if (!shaderFile) {
                
                MACH_ERROR_MSG("Could not open the file: " + shaderPath);
                return MACH_RAW_SHADERS();
            }

            shaderFile.open(shaderPath);
            size_t size = shaderFile.tellg();

            if (size != -1)
                MACH_MSG("Loaded: " + shaderPath);
            else
                MACH_ERROR_MSG("Failed to read from the file: " + shaderPath);

            if (shaderFile.is_open()) {

                std::string line;
                while (std::getline(shaderFile, line)) {

                    if (line[0] == '%') {

                        //Remove white space 
                        line.erase(std::remove_if(line.begin(), line.end(), 
                            [](char c) {
                                return std::isspace(static_cast<unsigned char>(c));
                            }), line.end());

                        if (line == "%vertex_shader") {

                            shaders[SupportedShaders::VERTEX] = "";
                            currentShader = SupportedShaders::VERTEX;
                        }
                        else  if (line == "%fragment_shader") {

                            shaders[SupportedShaders::FRAGMENT] = "";
                            currentShader = SupportedShaders::FRAGMENT;
                        }
                        else {

                            MACH_ERROR_MSG("In: " + shaderPath + " the shader type: " + line + " is not supported");
                            break;
                        }
                    } 
                    else {
                        if (currentShader != SupportedShaders::NON) {

                            if (currentShader == SupportedShaders::VERTEX) shaders[SupportedShaders::VERTEX] += line + '\n';
                            if (currentShader == SupportedShaders::FRAGMENT) shaders[SupportedShaders::FRAGMENT] += line + '\n';
                        }
                    }
                }
            }

            shaderFile.close();
            return shaders;
        }

        void Shader::compileVulkanBinaries(const std::unordered_map<SupportedShaders, std::string>& shaders) {

            shaderc::Compiler compiler;
            shaderc::CompileOptions options;
            options.SetTargetEnvironment(shaderc_target_env_vulkan, shaderc_env_version_vulkan_1_2);
            
            const bool optimize = true;
            if (optimize) options.SetOptimizationLevel(shaderc_optimization_level_performance);
            
            std::filesystem::path cacheDirectory = m_cacheDirectory;
            
            auto& shaderData = m_vulkanShaders;
            shaderData.clear();
            
            for (auto&& [shader, source] : shaders) {
                
                std::filesystem::path cacheDirectory = m_cacheDirectory;
                std::filesystem::path cachedPath;
                 
                switch (shader) {

                    case SupportedShaders::VERTEX: 
                        cachedPath = cacheDirectory / (m_fileName + ".cached_vert");
                        break;


                    case SupportedShaders::FRAGMENT:
                        cachedPath = cacheDirectory / (m_fileName + ".cached_frag");
                        break;
                }

                std::ifstream in(cachedPath, std::ios::in | std::ios::binary);

                if (in.is_open()) {
                
                    in.seekg(0, std::ios::end);
                    auto size = in.tellg();
                    in.seekg(0, std::ios::beg);

                    auto& data = shaderData[shader];
                    data.resize(size / sizeof(uint32_t));
                    in.read((char*)data.data(), size);
                }  
                else {

                    shaderc::SpvCompilationResult module = compiler.CompileGlslToSpv(source, getSupportedShaderVulkan(shader), m_shaderPath.c_str(), options);

                    if (module.GetCompilationStatus() != shaderc_compilation_status_success) 
                        MACH_ERROR_MSG("Failed to compile shader: " + m_shaderPath);
                
                    shaderData[shader] = std::vector<uint32_t>(module.cbegin(), module.cend());

                    std::ofstream out(cachedPath, std::ios::out | std::ios::binary);

                    if (out.is_open()) {

                        auto& data = shaderData[shader];
                        out.write((char*)data.data(), data.size() * sizeof(uint32_t));
                        out.flush();
                        out.close();
                    }
                }
            }
        }

        void Shader::compileOpenGLBinaries(const MACH_RAW_SHADERS& shaders) {

            compileVulkanBinaries(shaders);

            shaderc::Compiler compiler;
            shaderc::CompileOptions options;
            options.SetTargetEnvironment(shaderc_target_env_opengl, shaderc_env_version_opengl_4_5);

            const bool optimize = true;
            if (optimize) options.SetOptimizationLevel(shaderc_optimization_level_performance);
            std::filesystem::path cacheDirectory = m_cacheDirectory;
            
            auto& shaderData = m_OpenGLShaders;
            shaderData.clear();
            m_OpenGLSource.clear();

            for (auto&& [shader, spirv] : m_vulkanShaders) {

                std::filesystem::path cacheDirectory = m_cacheDirectory;
                std::filesystem::path cachedPath;

                spirv_cross::CompilerGLSL glslCompiler(spirv);
                m_OpenGLSource[shader] = glslCompiler.compile();
                auto& source = m_OpenGLSource[shader];

                shaderc::SpvCompilationResult module;

                switch (shader) {

                case SupportedShaders::VERTEX:
                    cachedPath = cacheDirectory / (m_fileName + ".cached_vert");
                    break;


                case SupportedShaders::FRAGMENT:
                    cachedPath = cacheDirectory / (m_fileName + ".cached_frag");
                    break;
                }

                if (module.GetCompilationStatus() != shaderc_compilation_status_success)
                    MACH_ERROR_MSG("Failed to compile shader: " + m_shaderPath);

                shaderData[shader] = std::vector<uint32_t>(module.cbegin(), module.cend());

                std::ofstream out(cachedPath, std::ios::out | std::ios::binary);

                if (out.is_open()) {

                    auto& data = shaderData[shader];
                    out.write((char*)data.data(), data.size() * sizeof(uint32_t));
                    out.flush();
                    out.close();
                }
            }
        }
    }
}
