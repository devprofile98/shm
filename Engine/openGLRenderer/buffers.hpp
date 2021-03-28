#ifndef SHM_OPENGL_BUFFERS_H
#define SHM_OPENGL_BUFFERS_H

#include <stdint.h>
#include <iostream>
#include <glad/glad.h>
#include "shader.hpp"
#include <utility>
#include <vector>
#include <string>

namespace SHM{
    namespace BUFFERS{

    // create new ubo and return it's index
    int createNewUBO(std::string uniform_block_name ,uint32_t buffer_size, int *binding_point_index);

    void uploadSubDataToUBO(uint32_t buffer_index, const glm::vec4 &data, uint32_t offset=0, uint32_t size=0);
    void uploadSubDataToUBO(uint32_t buffer_index, const glm::mat4 &data, uint32_t offset=0);
    void uploadSubDataToUBO(uint32_t buffer_index, const glm::vec3 &data, uint32_t offset=0);


    }
}
#endif // BUFFERS_H
