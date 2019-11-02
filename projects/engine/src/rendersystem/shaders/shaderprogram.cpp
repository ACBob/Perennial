#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "rendersystem/glerrors.h"
#include <iostream>

#include "shaderprogram.h"
namespace perennial{
	namespace shaders{
		GLuint createShaderProgram(GLuint VertexShader, GLuint FragmentShader){
			
			int  success;
			char infoLog[512];
			
			GLuint ShaderProgramId = glCreateProgram();

			std::cout << VertexShader << "  " << FragmentShader << std::endl;

			glAttachShader(ShaderProgramId, VertexShader);
			perennial::rendering::glCheckError();
			glAttachShader(ShaderProgramId, FragmentShader);
			perennial::rendering::glCheckError();

			glLinkProgram(ShaderProgramId);


			glGetProgramiv(ShaderProgramId, GL_LINK_STATUS, &success);
			if(!success) {
				glGetProgramInfoLog(ShaderProgramId, 512, NULL, infoLog);
				std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED" << std::endl;
				std::cout << infoLog << std::endl;
			}

			return ShaderProgramId;
		}
        void init_shader_system(){

            //Positions
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
			//Colours
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3* sizeof(float)));
			glEnableVertexAttribArray(1);
			//TexCoords
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
			glEnableVertexAttribArray(2);

        }
	}
}
