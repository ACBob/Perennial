#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H
#include "GLFW/glfw3.h"
extern "C"{
namespace perennial{
	namespace shaders{
		GLuint createShaderProgram(GLuint VertexShader, GLuint FragmentShader);
	}
}}
#endif
