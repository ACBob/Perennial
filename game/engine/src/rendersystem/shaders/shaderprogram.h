#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_Hs
#include "GLFW/glfw3.h"
namespace perennial{
    namespace shaders{
        GLuint CreateShaderProgram(GLuint VertexShader, GLuint FragmentShader);
    }
}
#endif
