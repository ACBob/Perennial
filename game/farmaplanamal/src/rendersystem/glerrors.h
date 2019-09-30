#include "GLFW/glfw3.h"
namespace perennial{
    namespace rendering{
        GLenum glCheckError_(const char *file, int line);
        #define glCheckError() glCheckError_(__FILE__, __LINE__)
    }
}