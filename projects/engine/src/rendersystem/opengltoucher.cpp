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
#include "shaders/shadersystem.h"
#include "rendersystem/shaders/shaderprogram.h"
#include "rendersystem/textures/texturesystem.h"

#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace perennial{

    namespace rendering{

        GLFWwindow* GameWindow;

        unsigned int VBO;
        perennial::shaders::ShaderProgram shaderProgram;
        unsigned int VAO;
        unsigned int EBO;

        unsigned int texture;

        int projLoc;
        int viewLoc;
        int modelLoc;

        glm::mat4 proj;
        glm::mat4 view;
        glm::mat4 model;

        
        float triVerts[] = {
            -0.5f, -0.5f, -0.5f, 1.0f,1.0f,1.0f,  0.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 1.0f,1.0f,1.0f, 1.0f, 0.0f,
            0.5f,  0.5f, -0.5f, 1.0f,1.0f,1.0f, 1.0f, 1.0f,
            0.5f,  0.5f, -0.5f, 1.0f,1.0f,1.0f, 1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f, 1.0f,1.0f,1.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 1.0f,1.0f,1.0f, 0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f, 1.0f,1.0f,1.0f, 0.0f, 0.0f,
            0.5f, -0.5f,  0.5f, 1.0f,1.0f,1.0f, 1.0f, 0.0f,
            0.5f,  0.5f,  0.5f, 1.0f,1.0f,1.0f, 1.0f, 1.0f,
            0.5f,  0.5f,  0.5f, 1.0f,1.0f,1.0f, 1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f, 1.0f,1.0f,1.0f, 0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f, 1.0f,1.0f,1.0f, 0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f, 1.0f,1.0f,1.0f, 1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f, 1.0f,1.0f,1.0f, 1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 1.0f,1.0f,1.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 1.0f,1.0f,1.0f, 0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f, 1.0f,1.0f,1.0f, 0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f, 1.0f,1.0f,1.0f, 1.0f, 0.0f,

            0.5f,  0.5f,  0.5f, 1.0f,1.0f,1.0f, 1.0f, 0.0f,
            0.5f,  0.5f, -0.5f, 1.0f,1.0f,1.0f, 1.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 1.0f,1.0f,1.0f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 1.0f,1.0f,1.0f, 0.0f, 1.0f,
            0.5f, -0.5f,  0.5f, 1.0f,1.0f,1.0f, 0.0f, 0.0f,
            0.5f,  0.5f,  0.5f, 1.0f,1.0f,1.0f, 1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f, 1.0f,1.0f,1.0f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 1.0f,1.0f,1.0f, 1.0f, 1.0f,
            0.5f, -0.5f,  0.5f, 1.0f,1.0f,1.0f, 1.0f, 0.0f,
            0.5f, -0.5f,  0.5f, 1.0f,1.0f,1.0f, 1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f, 1.0f,1.0f,1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, 1.0f,1.0f,1.0f, 0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f, 1.0f,1.0f,1.0f, 0.0f, 1.0f,
            0.5f,  0.5f, -0.5f, 1.0f,1.0f,1.0f, 1.0f, 1.0f,
            0.5f,  0.5f,  0.5f, 1.0f,1.0f,1.0f, 1.0f, 0.0f,
            0.5f,  0.5f,  0.5f, 1.0f,1.0f,1.0f, 1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f, 1.0f,1.0f,1.0f, 0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f, 1.0f,1.0f,1.0f, 0.0f, 1.0f
        };   
        unsigned int indices[] = {
            //0, 1, 3, // first triangle
            //1, 2, 3  // second triangle
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

            //TEXTURE STUFF!

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); //We're a pixelart. We don't do stretches here.

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            printf("perennial::render::compile_vertex\n");
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
            unsigned int VBO, VAO, EBO;

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
            glGenBuffers(1, &EBO);
            if (!EBO)
            {
                std::cout << "We've fucked up the EBO." << std::endl;
                return -1;
            }

            perennial::rendering::VAO = VAO;
            perennial::rendering::VBO = VBO;
            perennial::rendering::EBO = EBO;
            // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
            glBindVertexArray(VAO);

            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(perennial::rendering::triVerts), perennial::rendering::triVerts, GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(perennial::rendering::indices), perennial::rendering::indices, GL_STATIC_DRAW);


            //Positions
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            //Colours
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3* sizeof(float)));
            glEnableVertexAttribArray(1);
            //TexCoords
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
            glEnableVertexAttribArray(2);  

            // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
            glBindBuffer(GL_ARRAY_BUFFER, 0); 

            // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
            // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
            glBindVertexArray(0); 

            texture = perennial::rendering::textures::MakeTexture(std::string("textures/wall.jpg"));

            printf("perennial::render::init_end\n");


            glm::mat4 model = glm::mat4(1.0f);
            model = glm::rotate(model, glm::radians(55.0f), glm::vec3(1.0f, 0.0f, 0.0f)); 
            
            glm::mat4 view = glm::mat4(1.0f);
            // note that we're translating the scene in the reverse direction of where we want to move
            view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)); 

            glm::mat4 projection;
            projection = glm::perspective(glm::radians(-45.0f), (float)(800 / 600), 0.1f, 100.0f);

            perennial::rendering::proj = projection;
            perennial::rendering::model = model;
            perennial::rendering::view = view;

            int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
            int projectionLoc = glGetUniformLocation(shaderProgram.ID, "projection");
            glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));


            perennial::rendering::projLoc = projectionLoc;
            perennial::rendering::modelLoc = modelLoc;
            perennial::rendering::viewLoc = viewLoc;

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
            //std::cout << perennial::rendering::VAO << std::endl;
            glBindTexture(GL_TEXTURE_2D, perennial::rendering::texture);

            int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(perennial::rendering::model));
            int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(perennial::rendering::view));
            int projectionLoc = glGetUniformLocation(shaderProgram.ID, "projection");
            glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(perennial::rendering::proj));

            glDrawArrays(GL_TRIANGLES, 0, 36);
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