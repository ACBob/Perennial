#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H
extern "C"{
#include "GLFW/glfw3.h"
namespace perennial{
    namespace shaders{
        GLuint createShaderProgram(GLuint VertexShader, GLuint FragmentShader);
    }
}}
#endif
