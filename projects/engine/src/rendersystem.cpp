//-- Perennial File
//--- Purpose: Rendering system

/*
 _______
 |/     |
 |      ☹
 |     /|\
 |     / \
 |
/-\

4 Letter Word: D O O M
Hint: Adjective

J A Z C F N

*/


//Includes
#include <stdio.h>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include "rendersystem.h"

GLFWwindow* GameWindow;

float[3] Triangle = { 0.0f, 0.0f, 
                      1.0f, 0.0f,
                      0.0f, 1.0f};

int InitRenderSystem()
{
    //Init GLFW
    if (!glfwInit())
    {
        printf("Rendering System Error\n");
        return -1;
    }

    //Make our GameWindow
    GameWindow = glfwCreateWindow(800,600, "Perennial Window", NULL, NULL);
    if (!GameWindow)
    {
        printf("Unable to create window\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(GameWindow);

    //Setup Window Hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //Initialize Glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Unable to initialize GLAD\n");
        return -1;
    }   
    
    glViewport(0, 0, 800, 600);
    //glfwSetFramebufferSizeCallback(GameWindow, ResizeEvent);  

    return 0;
}

void ResizeEvent(GLFWwindow* Window, int Width, int Height)
{
    glViewport(0, 0, Width, Height);
}

int RenderSystem()
{

    while (!glfwWindowShouldClose(GameWindow))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(GameWindow);

        glfwPollEvents();
    }    
    
    glfwTerminate();
    return 0;
}
