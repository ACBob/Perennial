#include <string>

#ifndef SHADER_H
#define SHADER_H

#include "glad/glad.h"

class Shader
{
    private:
        unsigned int VertexID;
        unsigned int FragmentID;
        unsigned int ProgramID;
    public:
        Shader(std::string VertexPath, std::string FragmentPath);
        ~Shader();

        unsigned int GetProgId();
};

#endif
