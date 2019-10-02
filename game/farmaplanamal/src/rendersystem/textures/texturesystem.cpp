#include "include/stb/stb_image.h"
#include "glad/glad.h"
#include "texturesystem.h"
namespace perennial{
    namespace rendering{
        namespace textures{
            /*int LoadImage(char* FilePath){
                int width, height, nrChannels;
                unsigned char *data = stbi_load(FilePath, &width, &height, &nrChannels, 0); 
                stbi_image_free(data);
                return width, height, nrChannels;
            }*/
            GLuint MakeTexture(char* FilePath){
                
                int width, height, nrChannels;
                unsigned char *data = stbi_load(FilePath, &width, &height, &nrChannels, 0); 
                stbi_image_free(data);
                return width, height, nrChannels;
                unsigned int texture;
                glGenTextures(1, &texture);

                glBindTexture(GL_TEXTURE_2D, texture);  

                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);

            }
        }
    }
}
