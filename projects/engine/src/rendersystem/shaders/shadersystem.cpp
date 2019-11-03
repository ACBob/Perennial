#include "include/glad/glad.h"
#include "GLFW/glfw3.h"
#include "fileio/open.h"
#include "shadersystem.h"
#include "shaderprogram.h"
#include "rendersystem/glerrors.h"
#include <iostream>
#include <string>
namespace perennial{
	namespace shaders{
		GLuint loadShader(std::string ShaderFileName, int ShaderType){
			std::cout << "PERENNIAL::SHADERS::LOADSHADER::LOAD_PATH : " << ShaderFileName << std::endl;
			std::string ShaderFileLines = perennial::fileio::s_openFile(ShaderFileName);

			const char* ShaderSource = ShaderFileLines.c_str();

			GLuint ShaderObject = glCreateShader(ShaderType);
			if (ShaderObject==0)
			{
				std::cout << "Failed to Create Shader " << ShaderFileName << std::endl;
				return 0;
			}

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

		Shader::Shader(const std::string Vsrc, const std::string Fsrc){
            int  success;
			char infoLog[512];

            printf("Compile Vertex\n");
			int vertexId = perennial::shaders::loadShader(Vsrc, GL_VERTEX_SHADER);
            printf("Compile Fragment\n");
            int fragmentId = perennial::shaders::loadShader(Fsrc, GL_FRAGMENT_SHADER);
			
			GLuint ShaderProgramId = glCreateProgram();

			std::cout << vertexId << "  " << fragmentId << std::endl;

			glAttachShader(ShaderProgramId, vertexId);
			perennial::rendering::glCheckError();
			glAttachShader(ShaderProgramId, fragmentId);
			perennial::rendering::glCheckError();

			glLinkProgram(ShaderProgramId);


			glGetProgramiv(ShaderProgramId, GL_LINK_STATUS, &success);
			if(!success) {
				glGetProgramInfoLog(ShaderProgramId, 512, NULL, infoLog);
				std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED" << std::endl;
				std::cout << infoLog << std::endl;
			}
            this->ID = ShaderProgramId;
            glDeleteShader(vertexId);
            glDeleteShader(fragmentId);
		}
		Shader::~Shader(){
			std::cout << "Shader Destructor Called" << std::endl;
			this->deleteThis();
		}
		GLuint Shader::getId()
		{
			return this->ID;
		}
        void Shader::use()
        {
            glUseProgram(this->ID);
        }
		void Shader::deleteThis()
		{
			glDeleteProgram(this->ID);
		}
	}
}
