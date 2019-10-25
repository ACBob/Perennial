#ifndef INPUT_H
#define INPUT_H

#include "GLFW/glfw3.h"

extern "C"{
namespace perennial{
	namespace input{
		void processInput();
		bool b_checkClose();
		void mouseEvent(GLFWwindow* Window, double dXPos, double dYPos);
	}
}}
#endif
