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
#include "shader.h"

GLFWwindow* GameWindow;

#ifdef TEST_TRIANGLE
    
    float Triangle[] = { 0.0f, 0.0f, 0.0f,
                        1.0f, 0.0f, 0.0f,
                        0.0f, 1.0f, 0.0f,};
    unsigned int TriangleVBO;
    //unsigned int Triangle

#endif

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


    glClearColor(0.36f,0.1f,0.25f,1.0f);

    #ifdef TEST_TRIANGLE
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Triangle), Triangle, GL_STATIC_DRAW);
    #endif

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
