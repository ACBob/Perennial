/*
 * This file Touches our OpenGL.
 * Ooh Lovely.
 */

#include <glad/glad.h>
#include "GLFW/glfw3.h"

#include <stdio.h>
#include <iostream>

#include "opengltoucher.h"

namespace perennial{

    namespace rendering{

        GLFWwindow* GameWindow = NULL;

        unsigned int VBO = NULL;
        unsigned int shaderProgram = NULL;
        unsigned int VAO = NULL;

        float triVerts[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f,  0.5f, 0.0f
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

            glfwInit();
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            #ifdef __APPLE__
                glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //Don't worry, Apple is UNIX so we will do this.
            #endif

            const char *vertexShaderSource = 
                "#version 330 core\n"
                "layout (location = 0) in vec3 aPos;\n"
                "void main()\n"
                "{\n"
                    "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                "}\n";

            const char *fragmentShaderSource =
                "#version 330 core\n"
                "out vec4 FragColor;\n"
                "void main()\n"
                "{\n"
                    "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                "}\n";


            GLFWwindow* GameWindow = glfwCreateWindow(800, 600, "Perennial Window", NULL, NULL);
            perennial::rendering::GameWindow = GameWindow;
            if (perennial::rendering::GameWindow == NULL)
            {
                printf("Failed to create GLFW window\n");
                glfwTerminate();
                return -1;
            }
            glfwMakeContextCurrent(perennial::rendering::GameWindow);

            if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            {
                printf("Failed to initialize GLAD\n");
                return -1;
            }    

            glViewport(0, 0, 800, 600);

            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

            unsigned int VAO;
            glGenVertexArrays(1, &VAO);  

            glBindVertexArray(VAO);

            unsigned int VBO;
            glGenBuffers(1, &VBO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);

            glBufferData(GL_ARRAY_BUFFER, sizeof(triVerts), triVerts, GL_STATIC_DRAW);

            unsigned int vertexShader;
            vertexShader = glCreateShader(GL_VERTEX_SHADER);

            int  success;
            char infoLog[512];

            glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
            glCompileShader(vertexShader);

            glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);


            if(!success)
            {
                glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
                std::cout<<"ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"<<infoLog<<"\n";
            }

            unsigned int fragmentShader;
            fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
            glCompileShader(fragmentShader);

            glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

            if(!success)
            {
                glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
                std::cout<<"ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"<<infoLog<<"\n";
            }

            unsigned int shaderProgram;
            shaderProgram = glCreateProgram();


            glAttachShader(shaderProgram, vertexShader);
            glAttachShader(shaderProgram, fragmentShader);
            glLinkProgram(shaderProgram);

            glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
            if(!success) {
                glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
                std::cout<<"ERROR::SHADER::PROGRAM::LINK_FAILED\n"<<infoLog<<"\n";
            }
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);  

            glUseProgram(shaderProgram);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0); 

            return 0;

        }

        void Frame()
        {
            glClear(GL_COLOR_BUFFER_BIT); //Clear the screen every frame
            
            glUseProgram(shaderProgram);
            glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
            glDrawArrays(GL_TRIANGLES, 0, 3);
        }

        void FinishFrame()
        {
            glfwSwapBuffers(perennial::rendering::GameWindow);
            glfwPollEvents();
        }

        void Cleanup()
        {
            glfwTerminate(); 
        }

    }

}