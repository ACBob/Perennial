#ifndef TEXTURE_SYSTEM_H
#define TEXTURE_SYSTEM_H
extern "C"{

#include "glad/glad.h"
#include <string>
namespace perennial{
    namespace rendering{
        namespace textures{
            GLuint makeTexture(std::string FilePath);
        }
    }
}}
#endif