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
#include"shaders/shaderloader.h"

namespace perennial{

    namespace rendering{

        GLFWwindow* GameWindow;

        unsigned int VBO;
        unsigned int shaderProgram;
        unsigned int VAO;

        float triVerts[] = {
            // first triangle
            0.5f,  0.5f, 0.0f,  // top right
            0.5f, -0.5f, 0.0f,  // bottom right
            -0.5f,  0.5f, 0.0f,  // top left 
            // second triangle
            0.5f, -0.5f, 0.0f,  // bottom right
            -0.5f, -0.5f, 0.0f,  // bottom left
            -0.5f,  0.5f, 0.0f   // top left
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
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
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

            glViewport(0, 0, 800, 600);
            glCheckError();
            glClearColor(0.7f, 0.2f, 0.4f, 1.0f);


            unsigned int vertexShader;
            vertexShader = perennial::shaders::LoadShader("shaders/vertex.glsl",GL_VERTEX_SHADER);
            printf("perennial::render::compile_fragment\n");
            unsigned int fragmentShader;
            fragmentShader = perennial::shaders::LoadShader("shaders/fragment.glsl",GL_FRAGMENT_SHADER);

            unsigned int shaderProgram;
            shaderProgram = glCreateProgram();

            int success;
            char infoLog[512];

            printf("perennial::render::make_program\n");
            glAttachShader(shaderProgram, vertexShader);
            glAttachShader(shaderProgram, fragmentShader);
            glLinkProgram(shaderProgram);
            glCheckError();

            glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
            if(!success) {
                glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
                std::cout<<"ERROR::SHADER::PROGRAM::LINK_FAILED\n"<<infoLog<<"\n";
            }
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader); 
            glCheckError(); 

            printf("perennial::render::generate_vao\n");
            unsigned int VAO;
            glGenVertexArrays(1, &VAO);  
            glCheckError();
            glBindVertexArray(VAO);
            glCheckError();
            printf("perennial::render::generate_vbo\n");
            unsigned int VBO;
            glGenBuffers(1, &VBO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glCheckError();


            glBufferData(GL_ARRAY_BUFFER, sizeof(triVerts), triVerts, GL_STATIC_DRAW);
            glCheckError();

            glUseProgram(shaderProgram);
            glCheckError();

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            glCheckError(); 

            printf("perennial::render::init_end\n");

            return 0;

        }

        void Frame()
        {
            //glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT); //Clear the screen every frame
            glGetError();
            
            glUseProgram(shaderProgram);
            glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
            glDrawArrays(GL_TRIANGLES, 0, 3);
            glBindVertexArray(0);

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