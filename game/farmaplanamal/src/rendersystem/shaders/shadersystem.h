#include "glad/glad.h"
#include <string>

namespace perennial{
    namespace rendering{
        class Shader
        {
            public:
                GLuint ID;
                Shader(const std::string FilePath, GLuint Type);
                ~Shader();

                GLuint GetId();
                void Delete();
        };

        class ShaderProgram
        {
            public:
                GLuint ID;
                ShaderProgram(const GLuint Vertex, const GLuint Fragment);
                ~ShaderProgram();

                GLuint GetId();
                void Use();
                void Delete();
        };
    }
}
