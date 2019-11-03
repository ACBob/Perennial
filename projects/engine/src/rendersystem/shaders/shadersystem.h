#ifndef SHADER_SYSTEM_H
#define SHADER_SYSTEM_H
#include "GLFW/glfw3.h"
#include <string>
extern "C"{

namespace perennial{
	namespace shaders{
		class Shader
		{
			public:
				GLuint ID;
				Shader();
				Shader(const std::string Vsrc, const std::string Fsrc);
				~Shader();

				GLuint getId();
                void use();
				void deleteThis();
		};

	}
}}
#endif
