#ifndef Utility_H
#define Utility_H

//#include <Core.hpp>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace SHM {

    // ---------------------------------
    // base utility class for common functionality needed
    // in SHM such as:
    // 1- buffer operation: upload , manipulation
    // 2-
    // ---------------------------------

    class Utility{
    public:
        Utility(){}
        ~Utility(){}

        // ---------------------------------
        // creating world default Scene
        // creating UBO's and uploading default data
        // such as :  Light ub, VPMatrices ub
        // ---------------------------------
        virtual void InitWorld() =0;

        // create new uniform block object  and return it's index
        virtual int createNewGlobalBlock(std::string uniform_block_name, uint32_t buffer_size, int *index) =0;

        // uploading differnet data type to GPU memory
        virtual void uploadVec3(uint32_t buffer_index, const glm::vec3 &data, uint32_t offset, uint32_t size) = 0;
        virtual void uploadVec4(uint32_t buffer_index, const glm::vec4 &data, uint32_t offset, uint32_t size) = 0;
        virtual void uploadMat4(uint32_t buffer_index, const glm::mat4 &data, uint32_t offset, uint32_t size) = 0;
        virtual void uploadFloat(uint32_t buffer_index, const float &data, uint32_t offset, uint32_t size) = 0;

    };
}

#endif // Utility_H
