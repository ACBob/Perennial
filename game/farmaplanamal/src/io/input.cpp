#include "input.h"
#include "rendersystem/opengltoucher.h"
namespace perennial{
    namespace input{
        void ProcessInput()
        {

            if(perennial::rendering::GetKey(perennial::rendering::GameWindow,256) == 1)
            {
                perennial::rendering::SetWindowShouldClose(perennial::rendering::GameWindow,true);
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