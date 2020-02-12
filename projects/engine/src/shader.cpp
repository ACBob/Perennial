#include "fileoperations.h"
#include "shader.h"
#include "stdio.h"
#include <iostream>
#include <string>


Shader::Shader(const char *VertexPath, const char *FragmentPath)
{
    int Success;
    char Log[512];

    const char* VertexSource = OpenFile(VertexPath);
    const char* FragmentSource = OpenFile(FragmentPath);

    printf(VertexSource);
    std::cout << std::endl;
    std::cout << VertexSource << std::endl;

    this->VertexID = glCreateShader(GL_VERTEX_SHADER);
    this->FragmentID = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(this->VertexID, 1, &VertexSource, NULL);
    glCompileShader(this->VertexID);    
    glGetShaderiv(this->VertexID, GL_COMPILE_STATUS, &Success);

    if (!Success)
    {
        glGetShaderInfoLog(this->VertexID, 512, NULL, Log);
        printf("Shader Compilation Failed\n");
        printf(Log);
        printf("\n");
        printf("File source:\n");
        printf(VertexSource);
        printf("\n");
    }

    glShaderSource(this->FragmentID, 1, &FragmentSource, NULL);
    glCompileShader(this->FragmentID);    
    glGetShaderiv(this->FragmentID, GL_COMPILE_STATUS, &Success);

    if (!Success)
    {
        glGetShaderInfoLog(this->VertexID, 512, NULL, Log);
        printf("Shader Compilation Failed\n");
        printf(Log);
        printf("\n");
        printf("File source:\n");
        printf(FragmentSource);
        printf("\n");
    }

    this->ProgramID = glCreateProgram();

    
    glAttachShader(this->ProgramID, this->VertexID);
    glAttachShader(this->ProgramID, this->FragmentID);
    glLinkProgram(this->ProgramID);
    glGetProgramiv(this->ProgramID, GL_LINK_STATUS, &Success);

    if(!Success) {
        glGetProgramInfoLog(this->ProgramID, 512, NULL, Log);
        printf("Shader Linking Failed\n");
        printf(Log);
        printf("\n");

    }

}

Shader::~Shader()
{}

Shader::Shader()
{}

void Shader::Use()
{
    glUseProgram(this->ProgramID);
}

unsigned int Shader::GetProgId()
{
    return this->ProgramID;
}
