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

                GLuint GetId();
                void Delete();
        };

        class ShaderProgram
        {
            public:
                GLuint ID;
                ShaderProgram();
                ShaderProgram(const GLuint Vertex, const GLuint Fragment);
                ~ShaderProgram();

                GLuint GetId();
                void Use();
                void Delete();
        };
    }
}
#endif