#ifndef TEXTURE_SYSTEM_H
#define TEXTURE_SYSTEM_H
#include "glad/glad.h"
#include <string>
extern "C"{
namespace perennial{
	namespace rendering{
		namespace textures{
			GLuint makeTexture(std::string FilePath);
            void init_texture_system();
		}
	}
}}
#endif
