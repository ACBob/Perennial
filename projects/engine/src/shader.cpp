#include "fileoperations.h"
#include "shader.h"
#include "stdio.h"
#include <string>


Shader::Shader(std::string VertexPath, std::string FragmentPath)
{
    int Success;
    char Log[512];

    const char* VertexSource = OpenFile(VertexPath).c_str();
    const char* FragmentSource = OpenFile(FragmentPath).c_str();

    this->VertexID = glCreateShader(GL_VERTEX_SHADER);
    this->FragmentID = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(this->VertexID, 1, &VertexSource, NULL);
    glCompileShader(this->VertexID);    
    glGetShaderiv(this->VertexID, GL_COMPILE_STATUS, &Success);

    if (!Success)
    {
        glGetShaderInfoLog(this->VertexID, 512, NULL, Log);
        //printf("Shader Compilation Failed\n"+Log+"\n");
    }

    glShaderSource(this->FragmentID, 1, &FragmentSource, NULL);
    glCompileShader(this->FragmentID);    
    glGetShaderiv(this->FragmentID, GL_COMPILE_STATUS, &Success);

    if (!Success)
    {
        glGetShaderInfoLog(this->VertexID, 512, NULL, Log);
        //printf("Shader Compilation Failed\n"+Log+"\n");
    }

    this->ProgramID = glCreateProgram();

    
    glAttachShader(this->ProgramID, this->VertexID);
    glAttachShader(this->ProgramID, this->FragmentID);
    glLinkProgram(this->ProgramID);
    glGetProgramiv(this->ProgramID, GL_LINK_STATUS, &Success);

    if(!Success) {
        glGetProgramInfoLog(this->ProgramID, 512, NULL, Log);
        //printf("Program Linking Failed\n"+Log+"\n");
    }

}

unsigned int Shader::GetProgId()
{
    return this->ProgramID;
}
