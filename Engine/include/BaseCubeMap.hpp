#ifndef SHM_BASE_CUBEMAPS_H
#define SHM_BASE_CUBEMAPS_H

#include <memory>
#include "Core.hpp"
#include "shader.hpp"

namespace SHM {
class BaseCubeMap {
  public:
    virtual void Draw(const glm::mat4 &view_mat, const glm::mat4 &proj_mat) = 0;

  protected:
    unsigned int m_cube_texture_id, VAO, VBO;
    std::shared_ptr<shader> mShader;

  private:
    virtual bool load(std::vector<std::string> faces) = 0;
};
} // namespace SHM

#endif // SHM_BASE_CUBEMAPS_H
