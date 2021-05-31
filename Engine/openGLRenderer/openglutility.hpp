#ifndef SHM_OPENGLUTILITY_HPP
#define SHM_OPENGLUTILITY_HPP

#include "Utility.hpp"
#include "buffers.hpp"

namespace SHM {

    class openGLUtility : public Utility
    {
    public:
        openGLUtility();
        ~openGLUtility();
        void InitWorld() override;

        int createNewGlobalBlock(std::string uniform_block_name, uint32_t buffer_size, int *index) override;

        void uploadVec3(uint32_t buffer_index, const glm::vec3 &data, uint32_t offset, uint32_t size) override;
        void uploadVec4(uint32_t buffer_index, const glm::vec4 &data, uint32_t offset, uint32_t size) override;
        void uploadMat4(uint32_t buffer_index, const glm::mat4 &data, uint32_t offset, uint32_t size) override;
        void uploadFloat(uint32_t buffer_index, const float &data, uint32_t offset, uint32_t size) override;
    };

}
#endif // OPENGLUTILITY_HPP
