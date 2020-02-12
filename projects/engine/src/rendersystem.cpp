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

4 Letter Word: _ _ _ _
What it was: DooM

C T S H R P E

*/


//Includes
#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "rendersystem.h"
#include "shader.h"
#include "fileoperations.h"

GLFWwindow* GameWindow;
Shader GeoShader; //Geometry Shader, used for rendering the world.

#ifdef TEST_TRIANGLE
    
    float Triangle[] = { 0.0f, 0.0f, 0.0f,// 0.0f, 0.0f,
                         1.0f, 0.0f, 0.0f,// 1.0f, 0.5f,
                         0.0f, 1.0f, 0.0f};// 0.0f, 1.0f};
    unsigned int TriangleVBO;
    unsigned int TriangleVAO;

#endif

glm::mat4 Projection;
glm::mat4 View;

int InitRenderSystem()
{
    //Init GLFW
    if (!glfwInit())
    {
        printf("Rendering System Error\n");
        return -1;
    }

    //Setup Window Hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif

    //Make our GameWindow
    GameWindow = glfwCreateWindow(800,600, "Perennial Window", NULL, NULL);
    if (!GameWindow)
    {
        printf("Unable to create window\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(GameWindow);

    //Initialize Glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Unable to initialize GLAD\n");
        return -1;
    }   
    
    glViewport(0, 0, 800, 600);
    //glfwSetFramebufferSizeCallback(GameWindow, ResizeEvent);  

    Projection = glm::perspective(glm::radians(45.0f), (800.0f/600.0f), 0.1f, 100.0f);
    View = glm::mat4(1.0f);
    View = glm::translate(View, glm::vec3(0.0f, 0.0f, -3.0f));

    //Shaders
    GeoShader = Shader(&"./shader/vertex.glsl",&"./shader/fragment.glsl");

    glClearColor(0.36f,0.1f,0.25f,1.0f);

    #ifdef TEST_TRIANGLE //Buffer generation will, and should be, handled else-where. This is just so we can do stuff.
        glGenVertexArrays(1, &TriangleVAO);        

        glGenBuffers(1, &TriangleVBO);
        glBindBuffer(GL_ARRAY_BUFFER, TriangleVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Triangle), Triangle, GL_STATIC_DRAW);
    #endif

    //Setup Vertex Attribs
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    #ifdef TEST_TRIANGLE
        glBindVertexArray(TriangleVAO);
    #endif
      

    return 0;
}

void ResizeEvent(GLFWwindow* Window, int Width, int Height)
{
    glViewport(0, 0, Width, Height);
}

int RenderSystem()
{

    glfwMakeContextCurrent(GameWindow);

    while (!glfwWindowShouldClose(GameWindow))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        #ifdef TEST_TRIANGLE
            glUseProgram(GeoShader.GetProgId());
            glBindVertexArray(TriangleVAO);
            glDrawArrays(GL_TRIANGLES, 0, 3);
        #endif

        glfwSwapBuffers(GameWindow);

        glfwPollEvents();
    }    
    
    glfwTerminate();
    return 0;
}
