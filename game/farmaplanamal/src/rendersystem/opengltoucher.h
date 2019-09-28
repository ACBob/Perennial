#include "GLFW/glfw3.h"
namespace perennial{
    namespace rendering{
        extern GLFWwindow* GameWindow;
        
        int Init();
        int GetKey(GLFWwindow* GameWindow,int Key);
        void SetWindowShouldClose(GLFWwindow* GameWindow,bool shouldClose);
        void Frame();
        void Cleanup();
        void FinishFrame();
    }
}