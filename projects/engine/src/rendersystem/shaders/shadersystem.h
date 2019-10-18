#ifndef SHADER_SYSTEM_H
#define SHADER_SYSTEM_H
#include "GLFW/glfw3.h"
#include <string>

namespace perennial{
    namespace shaders{
        class Shader
        {
            public:
                GLuint ID;
                Shader();
                Shader(const std::string FilePath, GLuint Type);
                ~Shader();

                GLuint getId();
                void deleteThis();
        };

        class ShaderProgram
        {
            public:
                GLuint ID;
                ShaderProgram();
                ShaderProgram(const GLuint Vertex, const GLuint Fragment);
                ~ShaderProgram();

                GLuint getId();
                void use();
                void deleteThis();
        };
    }
}
#endif