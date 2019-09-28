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
    }
}