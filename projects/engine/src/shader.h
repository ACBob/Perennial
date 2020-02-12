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
        Shader();
        Shader(const char *VertexPath, const char *FragmentPath);
        ~Shader();

        void Use();
        unsigned int GetProgId();
};

#endif
