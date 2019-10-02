/*
 * This file Touches our OpenGL.
 * Ooh Lovely.
 */

#include <glad/glad.h>
#include "GLFW/glfw3.h"

#include <stdio.h>
#include <iostream>

#include "opengltoucher.h"
#include "glerrors.h"
#include"shaders/shadersystem.h"
#include "rendersystem/shaders/shaderprogram.h"

namespace perennial{

    namespace rendering{

        GLFWwindow* GameWindow;

        unsigned int VBO;
        perennial::shaders::ShaderProgram shaderProgram;
        unsigned int VAO;

        
        float triVerts[] = {
            // first triangle
            0.5f,  0.5f, 0.0f, 1.0f, 0.3f, 0.5f, // top right
            0.5f, -0.5f, 0.0f, 0.6f, 0.7f, 0.0f,  // bottom right
            -0.5f,  0.5f, 0.0f, 0.2f, 0.5f, 0.7f  // top left 
        };   

        int GetKey(GLFWwindow* GameWindow, int key)
        {
            return glfwGetKey(GameWindow,key);
        }

        void SetWindowShouldClose(GLFWwindow* GameWindow, bool shouldClose)
        {
            glfwSetWindowShouldClose(GameWindow,(int)shouldClose);
        }

        int Init(){

            printf("perennial::render::init\n");

            glfwInit();
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4.5);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4.5);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            #ifdef __APPLE__
                glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //Don't worry, Apple is UNIX so we will do this.
            #endif

            printf("perennial::render::create_window\n");
            GLFWwindow* GameWindow = glfwCreateWindow(800, 600, "Perennial Window", NULL, NULL);
            perennial::rendering::GameWindow = GameWindow;
            glCheckError();
            if (perennial::rendering::GameWindow == NULL)
            {
                printf("Failed to create GLFW window\n");
                glfwTerminate();
                return -1;
            }
            glfwMakeContextCurrent(perennial::rendering::GameWindow);
            printf("perennial::render::initialise_glad\n");
            if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            {
                printf("Failed to initialize GLAD\n");
                return -1;
            }    
            //glEnable(GL_DEBUG_OUTPUT);
            glDebugMessageCallback((GLDEBUGPROC)perennial::rendering::glDebugOutput, stderr);

            std::cout << "Detected Renderer Version: " << glGetString(GL_RENDERER) << std::endl;
            std::cout << "Detected Supported OpenGl Version: " << glGetString(GL_VERSION) << std::endl;

            glViewport(0, 0, 800, 600);
            glCheckError();
            glClearColor(0.7f, 0.2f, 0.4f, 1.0f);


            perennial::shaders::Shader vertexShader("shaders/vertex.glsl",GL_VERTEX_SHADER);
            printf("perennial::render::compile_fragment\n");
            perennial::shaders::Shader fragmentShader("shaders/fragment.glsl",GL_FRAGMENT_SHADER);
            
            printf("perennial::render::make_program\n");
            static perennial::shaders::ShaderProgram shaderProgram(vertexShader.ID,fragmentShader.ID);
            perennial::rendering::shaderProgram = shaderProgram;
            vertexShader.Delete();
            fragmentShader.Delete(); 
            glCheckError(); 

            printf("perennial::render::generate_vao and generate_vbo\n");
            unsigned int VBO, VAO;

            glGenVertexArrays(1, &VAO);
            if (!VAO)
            {
                std::cout << "We've fucked up the VAO." << std::endl;
                return -1;
            }
            std::cout << VAO << std::endl;
            glGenBuffers(1, &VBO);
            if (!VBO)
            {
                std::cout << "We've fucked up the VBO." << std::endl;
                return -1;
            }
            perennial::rendering::VAO = VAO;
            perennial::rendering::VBO = VBO;
            // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
            glBindVertexArray(VAO);

            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(triVerts), triVerts, GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
            glEnableVertexAttribArray(1);

            // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
            glBindBuffer(GL_ARRAY_BUFFER, 0); 

            // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
            // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
            glBindVertexArray(0); 


            printf("perennial::render::init_end\n");

            return 0;

        }

        void Frame()
        {
            glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clear the screen every frame
            glGetError();
            
            // draw our first triangle
            perennial::rendering::shaderProgram.Use();
            glBindVertexArray(perennial::rendering::VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
            glCheckError();
            std::cout << perennial::rendering::VAO << std::endl;
            glDrawArrays(GL_TRIANGLES, 0, 6);
            glCheckError();
            // glBindVertexArray(0); // no need to unbind it every time 

            glfwSwapBuffers(perennial::rendering::GameWindow);
            glfwPollEvents();
            
            glGetError();
        }

        void Cleanup()
        {
            glfwTerminate(); 
        }

        void SetMode(GLenum face, GLenum mode)
        {
            glPolygonMode(face, mode);
        }

    }

}