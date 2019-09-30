#include "input.h"
#include "GLFW/glfw3.h"
#include "rendersystem/opengltoucher.h"
namespace perennial{
    namespace input{
        bool WireFrame;
        void ProcessInput()
        {

            if(perennial::rendering::GetKey(perennial::rendering::GameWindow,GLFW_KEY_ESCAPE) == 1)
            {
                perennial::rendering::SetWindowShouldClose(perennial::rendering::GameWindow,true);
            }
            if(perennial::rendering::GetKey(perennial::rendering::GameWindow,GLFW_KEY_TAB))
            {
                perennial::rendering::SetMode(GL_FRONT_AND_BACK,(WireFrame) ? GL_LINE : GL_FILL);
                WireFrame = !WireFrame;
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