#include "openglutility.hpp"
#include "Logger.hpp"
namespace SHM {

openGLUtility::openGLUtility() { SHM::Logger::debug("OPENGL UTILITY CLASS CONSTRUCTED"); }
openGLUtility::~openGLUtility() { SHM::Logger::info("OPENGL UTILITY CLASS DECONSTRUCTED"); }

void openGLUtility::InitWorld() { SHM::Logger::info("OPENGL Utility Class Started!"); }

int openGLUtility::createNewGlobalBlock(std::string uniform_block_name, uint32_t buffer_size, int *index) {
    return BUFFERS::createNewUBO(uniform_block_name, buffer_size, index);
}

void openGLUtility::uploadVec3(uint32_t buffer_index, const glm::vec3 &data, uint32_t offset, uint32_t size) {
    BUFFERS::uploadSubDataToUBO(buffer_index, data, offset);
}

void openGLUtility::uploadVec4(uint32_t buffer_index, const glm::vec4 &data, uint32_t offset, uint32_t size) {
    BUFFERS::uploadSubDataToUBO(buffer_index, data, offset);
}

void openGLUtility::uploadMat4(uint32_t buffer_index, const glm::mat4 &data, uint32_t offset, uint32_t size) {
    BUFFERS::uploadSubDataToUBO(buffer_index, data, offset);
}

void openGLUtility::uploadFloat(uint32_t buffer_index, const float &data, uint32_t offset, uint32_t size) {
    BUFFERS::uploadSubDataToUBO(buffer_index, data, offset);
}
} // namespace SHM
