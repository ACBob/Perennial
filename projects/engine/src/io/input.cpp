#include "input.h"
#include "GLFW/glfw3.h"
#include "rendersystem/opengltoucher.h"
namespace perennial{
	namespace input{
		bool bWireFrame;
		bool bHitTab;
		void processInput()
		{

			if(perennial::rendering::getKey(perennial::rendering::GameWindow,GLFW_KEY_ESCAPE) == GLFW_PRESS)
			{
				perennial::rendering::setWindowShouldClose(perennial::rendering::GameWindow,true);
			}
			else if(perennial::rendering::getKey(perennial::rendering::GameWindow,GLFW_KEY_TAB) == GLFW_PRESS && !bHitTab)
			{
				perennial::rendering::setMode(GL_FRONT_AND_BACK,(bWireFrame) ? GL_LINE : GL_FILL);
				bHitTab = true;
				bWireFrame = !bWireFrame;
			}
			else if(perennial::rendering::getKey(perennial::rendering::GameWindow,GLFW_KEY_TAB) == GLFW_RELEASE)
			{
				bHitTab = false;
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
			perennial::rendering::active_camera->mouseUpdate(glm::vec2(dXPos,dYPos));
		}
	}
}
