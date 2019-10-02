#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "rendersystem/glerrors.h"
#include <iostream>

#include "shaderprogram.h"
namespace perennial{
    namespace shaders{
        GLuint CreateShaderProgram(GLuint VertexShader, GLuint FragmentShader){
            
            int  success;
            char infoLog[512];
            
            GLuint ShaderProgramId = glCreateProgram();

            glAttachShader(ShaderProgramId, VertexShader);
            perennial::rendering::glCheckError();
            glAttachShader(ShaderProgramId, FragmentShader);
            perennial::rendering::glCheckError();

            glLinkProgram(ShaderProgramId);


            glGetProgramiv(ShaderProgramId, GL_LINK_STATUS, &success);
            if(!success) {
                glGetProgramInfoLog(ShaderProgramId, 512, NULL, infoLog);
                std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED" << std::endl;
            }

            return ShaderProgramId;
        }
    }
}