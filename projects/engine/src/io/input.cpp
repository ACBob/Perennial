#include "input.h"
#include "GLFW/glfw3.h"
#include "rendersystem/opengltoucher.h"
#include <iostream>
namespace perennial{
	namespace input{
		bool bWireFrame;
		bool bHitTab;
		void keyEvent(GLFWwindow* Window, int iKey, int iScancode, int iAction, int iMods)
		{
            if (iKey == GLFW_KEY_TAB && iAction == GLFW_PRESS)
            {
                perennial::rendering::setMode(GL_FRONT_AND_BACK,(bWireFrame) ? GL_LINE : GL_FILL);
                bWireFrame = !bWireFrame;
            }
            
            if (iKey == GLFW_KEY_R && iAction == GLFW_PRESS)
            {
                std::cout << "Reload Shaders" << std::endl;
                perennial::rendering::remake_shaders();
            }
		}
		bool b_checkClose()
		{
			if(glfwWindowShouldClose(perennial::rendering::GameWindow))
			{
				perennial::rendering::cleanup();
				return true;
			}
			return false;
		}
		void mouseEvent(GLFWwindow* Window, double dXPos, double dYPos)
		{
			//perennial::rendering::active_camera->mouseUpdate(glm::vec2(dXPos,dYPos));
		}
	}
}
