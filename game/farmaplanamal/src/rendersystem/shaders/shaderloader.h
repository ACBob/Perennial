#include "GLFW/glfw3.h"
#include <string>
namespace perennial{
    namespace shaders{
        GLuint LoadShader(std::string FileName, int ShaderType);
    }
}