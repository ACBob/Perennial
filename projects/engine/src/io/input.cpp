#include "input.h"
#include "GLFW/glfw3.h"
#include "rendersystem/opengltoucher.h"
#include <cstdio>
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
            
            if (iKey == GLFW_KEY_R && iAction == GLFW_PRESS && iAction == GLFW_MOD_CONTROL)
                printf("Ctrl+R");
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
