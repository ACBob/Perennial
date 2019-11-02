#ifndef OPENGL_TOUCHER_H
#define OPENGL_TOUCHER_H
#include "GLFW/glfw3.h"
#include "shaders/shadersystem.h"
#include "camera.h"
extern "C"{
namespace perennial{
	namespace rendering{
		extern GLFWwindow* GameWindow;
		
		int i_init();
		int getKey(GLFWwindow* GameWindow,int Key);
		void setWindowShouldClose(GLFWwindow* GameWindow,bool shouldClose);
		void frame();
		void cleanup();
		void setMode(GLenum face, GLenum mode);

		extern Camera* active_camera;

		extern float triVerts[];
		extern unsigned int VBO;
		extern perennial::shaders::ShaderProgram shaderProgram;
		extern unsigned int VAO;
	}
}}
#endif
