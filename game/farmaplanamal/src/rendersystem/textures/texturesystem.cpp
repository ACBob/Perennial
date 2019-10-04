#define STB_IMAGE_IMPLEMENTATION
#include "include/stb/stb_image.h"
#include "glad/glad.h"
#include "texturesystem.h"
#include <string>
#include <iostream>

namespace perennial{
    namespace rendering{
        namespace textures{
            /*int LoadImage(char* FilePath){
                int width, height, nrChannels;
                unsigned char *data = stbi_load(FilePath, &width, &height, &nrChannels, 0); 
                stbi_image_free(data);
                return width, height, nrChannels;
            }*/
            GLuint MakeTexture(std::string FilePath){
                std::cout << "Loading Image " << FilePath << std::endl;
                int width, height, nrChannels;
                unsigned char *data = stbi_load(FilePath.c_str(), &width, &height, &nrChannels, 0); 
                unsigned int texture;
                std::cout << "Generating Image ID" << std::endl;
                glGenTextures(1, &texture);
                if (texture==0)
                {
                    std::cout << "Texture Generation for " << FilePath << " Failed!";
                    return 0;
                }

                std::cout << "Binding..." << std::endl;
                glBindTexture(GL_TEXTURE_2D, texture);  

                std::cout << "Applying Data..." << std::endl;
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                std::cout << "Generating Mipmaps" << std::endl;
                glGenerateMipmap(GL_TEXTURE_2D);

                std::cout << "Finished Loading Image " << FilePath << "!" << std::endl;
                stbi_image_free(data);
                return texture;

            }
        }
    }
}
