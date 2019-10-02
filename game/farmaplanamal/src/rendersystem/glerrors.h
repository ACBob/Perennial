#include "GLFW/glfw3.h"
namespace perennial{
    namespace rendering{
        GLenum glCheckError_(const char *file, int line);
        #define glCheckError() glCheckError_(__FILE__, __LINE__);
        void APIENTRY glDebugOutput(GLenum source, 
                                    GLenum type, 
                                    GLuint id, 
                                    GLenum severity, 
                                    GLsizei length, 
                                    const GLchar *message, 
                                    void *userParam);
    }
}