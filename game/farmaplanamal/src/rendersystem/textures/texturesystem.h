#ifndef TEXTURE_SYSTEM_H
#define TEXTURE_SYSTEM_H

#include "glad/glad.h"
#include <string>
namespace perennial{
    namespace rendering{
        namespace textures{
            GLuint MakeTexture(std::string FilePath);
        }
    }
}
#endif