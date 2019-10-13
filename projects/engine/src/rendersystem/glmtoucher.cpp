#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace perennial{
    namespace rendering_glm{
        void Orthographic(int height, int width){
            glm::ortho(0.0f, (float)height, 0.0f, (float)width, 0.1f, 100.0f);
        }
        void Projection(int height, int width){
            glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)width/(float)height, 0.1f, 100.0f);

            glm::mat4 model = glm::mat4(1.0f);
            model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f)); 

        }
    }
}