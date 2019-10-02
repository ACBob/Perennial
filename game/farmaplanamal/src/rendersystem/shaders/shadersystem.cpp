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
        GLuint LoadShader(std::string ShaderFileName, int ShaderType){
            std::cout << "PERENNIAL::SHADERS::LOADSHADER::LOAD_PATH : " << ShaderFileName << std::endl;
            std::string ShaderFileLines = perennial::fileio::OpenFile(ShaderFileName);

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

        class Shader{
            public:
                GLuint ID;
                Shader(const std::string FilePath,GLuint Type){
                    ID = LoadShader(FilePath,Type);
                }
                ~Shader(){
                    Delete();
                }
                GLuint GetId()
                {
                    return ID;
                }
                void Delete()
                {
                    glDeleteShader(ID);
                }
        };
        
        class ShaderProgram{
            public:
                GLuint ID;
                ShaderProgram(const GLuint Vertex, const GLuint Fragment){
                    ID = perennial::shaders::CreateShaderProgram(Vertex,Fragment);
                }
                ~ShaderProgram(){
                    Delete();
                }
                GLuint GetId()
                {
                    return ID;
                }
                void Use()
                {
                    glUseProgram(ID);
                }
                void Delete()
                {
                    glDeleteProgram(ID);
                }
        };
    }
}