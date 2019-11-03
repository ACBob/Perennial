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

		Shader::Shader()
		{
			std::cout << "Default Constructor for Shader, assuming NULL.";
			this->ID = 0;
		}
		Shader::Shader(const std::string FilePath,GLuint Type){
			this->ID = perennial::shaders::loadShader(FilePath,Type);
		}
		Shader::~Shader(){
			std::cout << "Shader Destructor Called" << std::endl;
			this->deleteThis();
		}
		GLuint Shader::getId()
		{
			return this->ID;
		}
		void Shader::deleteThis()
		{
			glDeleteShader(this->ID);
		}

		ShaderProgram::ShaderProgram()
		{
			std::cout << "Default constructor called for ShaderProgram, assuming NULL.";
			this->ID = 0;
		}
		ShaderProgram::ShaderProgram(const GLuint Vertex, const GLuint Fragment){
			this->ID = perennial::shaders::createShaderProgram(Vertex,Fragment);
		}
		ShaderProgram::~ShaderProgram(){
			std::cout << "ShaderProgram Destructor called" << std::endl;
			this->deleteThis();
		}
		GLuint ShaderProgram::getId()
		{
			return this->ID;
		}
		void ShaderProgram::use()
		{
			glUseProgram(ID);
		}
		void ShaderProgram::deleteThis()
		{
            std::cout << "ShaderProgram deleteThis Called" << std::endl;
			glDeleteProgram(this->ID);
		}
	}
}
