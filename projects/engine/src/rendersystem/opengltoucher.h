#ifndef OPENGL_TOUCHER_H
#define OPENGL_TOUCHER_H
#include "GLFW/glfw3.h"
#include "shaders/shadersystem.h"
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
        extern perennial::shaders::ShaderProgram shaderProgram;
        extern unsigned int VAO;
    }
}
#endif