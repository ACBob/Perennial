#include "GLFW/glfw3.h"
namespace perennial{
    namespace rendering{
        extern GLFWwindow* GameWindow;
        
        int Init();
        int GetKey(GLFWwindow* GameWindow,int Key);
        void SetWindowShouldClose(GLFWwindow* GameWindow,bool shouldClose);
        void Frame();
        void Cleanup();
        void SetMode(GLenum face, GLenum mode);

        extern float triVerts[];
        extern unsigned int VBO;
        extern unsigned int shaderProgram;
        extern unsigned int VAO;
    }
}