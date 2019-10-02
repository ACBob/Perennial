#include "input.h"
#include "GLFW/glfw3.h"
#include "rendersystem/opengltoucher.h"
namespace perennial{
    namespace input{
        bool WireFrame;
        bool HitTab;
        void ProcessInput()
        {

            if(perennial::rendering::GetKey(perennial::rendering::GameWindow,GLFW_KEY_ESCAPE) == GLFW_PRESS)
            {
                perennial::rendering::SetWindowShouldClose(perennial::rendering::GameWindow,true);
            }
            else if(perennial::rendering::GetKey(perennial::rendering::GameWindow,GLFW_KEY_TAB) == GLFW_PRESS && !HitTab)
            {
                perennial::rendering::SetMode(GL_FRONT_AND_BACK,(WireFrame) ? GL_LINE : GL_FILL);
                HitTab = true;
                WireFrame = !WireFrame;
            }
            else if(perennial::rendering::GetKey(perennial::rendering::GameWindow,GLFW_KEY_TAB) == GLFW_RELEASE)
            {
                HitTab = false;
            }

        }
        bool CheckClose()
        {
            if(glfwWindowShouldClose(perennial::rendering::GameWindow))
            {
                perennial::rendering::Cleanup();
                return true;
            }
            return false;
        }
    }
}