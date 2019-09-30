#include "include/glad/glad.h"
#include "GLFW/glfw3.h"
#include "fileio/open.h"
#include "shaderloader.h"
#include "rendersystem/glerrors.h"
#include <iostream>
#include <string>
namespace perennial{
    namespace shaders{
        GLuint LoadShader(std::string ShaderFileName, int ShaderType){
            std::cout << "PERENNIAL::SHADERS::LOADSHADER::LOAD_PATH : " << ShaderFileName << std::endl;
            std::string ShaderFileLines = perennial::fileio::OpenFile(ShaderFileName);

            const char* ShaderSource = ShaderFileLines.c_str();

            GLuint ShaderObject = glCreateShader(ShaderType);

            int  success;
            char infoLog[512];
            glShaderSource(ShaderObject, 1, &ShaderSource, NULL);
            glCompileShader(ShaderObject);
            perennial::rendering::glCheckError();

            glGetShaderiv(ShaderObject, GL_COMPILE_STATUS, &success);

            if(!success)
            {
                glGetShaderInfoLog(ShaderObject, 512, NULL, infoLog);
                std::cout<<"ERROR::SHADER::COMPILATION_FAILED\n"<<infoLog<<"\n";
                glDeleteShader(ShaderObject);
                return 0;
            }
            return ShaderObject;

        }
    }
}