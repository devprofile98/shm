#ifndef SHM_OPENGL_CUBEMAPS_H
#define SHM_OPENGL_CUBEMAPS_H

#include <memory>
#include "BaseCubeMap.hpp"
#include "shader.hpp"

namespace SHM {
namespace opengl {
class CubeMaps : public BaseCubeMap {
  public:
    CubeMaps();
    CubeMaps(std::vector<std::string> faces, std::shared_ptr<shader> sh);
    void Draw(const glm::mat4 &view_mat, const glm::mat4 &proj_mat) override;

  private:
    bool load(std::vector<std::string> faces) override;
};
} // namespace opengl
} // namespace SHM

#endif // SHM_OPENGL_CUBEMAPS_H