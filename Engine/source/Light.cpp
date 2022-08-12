#include "Light.hpp"

namespace SHM {
Light::Light() {}
Light::~Light() {}

void Light::setAmbient(const Color &color) {
    m_ambient = color;
    ambientChanged();
}

void Light::setSpecular(const Color &color) {
    m_specular = color;
    specularChanged();
}

void Light::setDiffuse(const Color &color) {
    m_diffuse = color;
    diffuseChanged();
}

DirectionalLight::DirectionalLight(float x, float y, float z) : direction(Vector3(x, y, z)) {}

DirectionalLight::DirectionalLight(const Vector3 &direction) : direction(direction) {}

DirectionalLight::~DirectionalLight() {}

void DirectionalLight::ambientChanged() {}

void DirectionalLight::diffuseChanged() {}

void DirectionalLight::specularChanged() {}

PointLight::PointLight(float x, float y, float z) : position(Vector3(x, y, z)) {}

PointLight::PointLight(const Vector3 &position, const Color &diffuse, const Color &specular, const Color &ambient)
    : position(position) {
    if (pointlight_lists.size() > 12) {
        std::cout << "Lights are full" << std::endl;
        return;
    }
    memory_offset = pointlight_lists.size() * (5 * sizeof(glm::vec4)) + (4 * sizeof(glm::vec4));
    setAmbient(ambient); // Color(0.72f,0.72f ,0.72f)
    setDiffuse(diffuse); // Color(0.92, 0.0, 0.0)
    setSpecular(specular);
    std::cout << "in point light class -------" << std::endl;

    Engine::GetEngine()->getRenderer()->GetUtility()->uploadVec4(Engine::GetEngine()->getRenderer()->ubo_lights,
                                                                 glm::vec4(position.x, position.y, position.z, 0.0f),
                                                                 memory_offset + int(member_offset::position), sizeof(glm::vec4));

    Engine::GetEngine()->getRenderer()->GetUtility()->uploadVec4(Engine::GetEngine()->getRenderer()->ubo_lights,
                                                                 glm::vec4(m_ambient.r, m_ambient.g, m_ambient.b, 0.0f),
                                                                 memory_offset + int(member_offset::ambient), sizeof(glm::vec4));

    Engine::GetEngine()->getRenderer()->GetUtility()->uploadVec4(Engine::GetEngine()->getRenderer()->ubo_lights,
                                                                 glm::vec4(m_diffuse.r, m_diffuse.g, m_diffuse.b, 0.0f),
                                                                 memory_offset + int(member_offset::diffuse), sizeof(glm::vec4));

    Engine::GetEngine()->getRenderer()->GetUtility()->uploadVec4(Engine::GetEngine()->getRenderer()->ubo_lights,
                                                                 glm::vec4(m_specular.r, m_specular.g, m_specular.b, 0.0f),
                                                                 memory_offset + int(member_offset::specular), sizeof(glm::vec4));

    Engine::GetEngine()->getRenderer()->GetUtility()->uploadVec4(
        Engine::GetEngine()->getRenderer()->ubo_lights, glm::vec4(1.0f, 0.35f, 0.44f, 0.0f),
        memory_offset + int(member_offset::properties), sizeof(glm::vec4));
    pointlight_lists.push_back(*this);
}

PointLight::~PointLight() {}

void PointLight::ambientChanged() {}

void PointLight::diffuseChanged() {}

void PointLight::specularChanged() {}
std::vector<PointLight> PointLight::pointlight_lists;

SpotLight::SpotLight(const Vector3 &direction, const Vector3 &position, const Color &diffuse, const Color &specular,
                     const Color &ambient)
    : direction(direction), position(position) {
    if (light_lists.size() > 12) {
        std::cout << "Lights are full" << std::endl;
        return;
    }
    memory_offset = light_lists.size() * (7 * sizeof(glm::vec4));
    setAmbient(ambient); // Color(0.72f,0.72f ,0.72f)
    setDiffuse(diffuse); // Color(0.92, 0.0, 0.0)
    setSpecular(specular);
    std::cout << "in spot light class -------" << std::endl;
    Engine::GetEngine()->getRenderer()->GetUtility()->uploadVec4(Engine::GetEngine()->getRenderer()->ubo_spots,
                                                                 glm::vec4(position.x, position.y, position.z, 0.0f),
                                                                 memory_offset + int(member_offset::position), sizeof(glm::vec4));

    Engine::GetEngine()->getRenderer()->GetUtility()->uploadVec4(Engine::GetEngine()->getRenderer()->ubo_spots,
                                                                 glm::vec4(direction.x, direction.y, direction.z, 0.0f),
                                                                 memory_offset + sizeof(glm::vec4), sizeof(glm::vec4));

    Engine::GetEngine()->getRenderer()->GetUtility()->uploadVec4(Engine::GetEngine()->getRenderer()->ubo_spots,
                                                                 glm::vec4(m_ambient.r, m_ambient.g, m_ambient.b, 0.0f),
                                                                 memory_offset + 2 * sizeof(glm::vec4), sizeof(glm::vec4));

    Engine::GetEngine()->getRenderer()->GetUtility()->uploadVec4(Engine::GetEngine()->getRenderer()->ubo_spots,
                                                                 glm::vec4(m_diffuse.r, m_diffuse.g, m_diffuse.b, 0.0f),
                                                                 memory_offset + 3 * sizeof(glm::vec4), sizeof(glm::vec4));

    Engine::GetEngine()->getRenderer()->GetUtility()->uploadVec4(Engine::GetEngine()->getRenderer()->ubo_spots,
                                                                 glm::vec4(m_specular.r, m_specular.g, m_specular.b, 0.0f),
                                                                 memory_offset + 4 * sizeof(glm::vec4), sizeof(glm::vec4));

    Engine::GetEngine()->getRenderer()->GetUtility()->uploadFloat(Engine::GetEngine()->getRenderer()->ubo_spots, 1.0f,
                                                                  memory_offset + 5 * sizeof(glm::vec4), sizeof(float));

    Engine::GetEngine()->getRenderer()->GetUtility()->uploadFloat(Engine::GetEngine()->getRenderer()->ubo_spots, 0.35f,
                                                                  memory_offset + 5 * sizeof(glm::vec4) + 4, sizeof(float));

    Engine::GetEngine()->getRenderer()->GetUtility()->uploadFloat(Engine::GetEngine()->getRenderer()->ubo_spots, 0.44f,
                                                                  memory_offset + 5 * sizeof(glm::vec4) + 8, sizeof(float));

    Engine::GetEngine()->getRenderer()->GetUtility()->uploadFloat(Engine::GetEngine()->getRenderer()->ubo_spots,
                                                                  glm::cos(glm::radians(12.5f)),
                                                                  memory_offset + 5 * sizeof(glm::vec4) + 12, sizeof(float));

    Engine::GetEngine()->getRenderer()->GetUtility()->uploadFloat(Engine::GetEngine()->getRenderer()->ubo_spots,
                                                                  glm::cos(glm::radians(17.5f)),
                                                                  memory_offset + 6 * sizeof(glm::vec4), sizeof(float));

    light_lists.push_back(*this);
    std::cout << light_lists.size() << std::endl;
    std::cout << "in spot light class +++++++++" << std::endl;
}

SpotLight::~SpotLight() {}

void SpotLight::setDiffuse1(const Color &color) {
    m_diffuse = color;
    std::cout << color.r << color.g << color.b << " " << int(member_offset::ambient) << std::endl;
    Engine::GetEngine()->getRenderer()->GetUtility()->uploadVec4(
        Engine::GetEngine()->getRenderer()->ubo_spots, glm::vec4(color.r, color.g, color.b, 0.0f),
        light_lists.size() * (7 * sizeof(glm::vec4)) + int(member_offset::diffuse), sizeof(glm::vec4));
}

void SpotLight::ambientChanged() {
    Engine::GetEngine()->getRenderer()->GetUtility()->uploadVec4(Engine::GetEngine()->getRenderer()->ubo_spots,
                                                                 glm::vec4(m_ambient.r, m_ambient.g, m_ambient.b, 0.0f),
                                                                 memory_offset + 2 * sizeof(glm::vec4), sizeof(glm::vec4));
}

void SpotLight::diffuseChanged() {
    Engine::GetEngine()->getRenderer()->GetUtility()->uploadVec4(Engine::GetEngine()->getRenderer()->ubo_spots,
                                                                 glm::vec4(m_diffuse.r, m_diffuse.g, m_diffuse.b, 0.0f),
                                                                 memory_offset + 3 * sizeof(glm::vec4), sizeof(glm::vec4));
}

void SpotLight::specularChanged() {
    Engine::GetEngine()->getRenderer()->GetUtility()->uploadVec4(Engine::GetEngine()->getRenderer()->ubo_spots,
                                                                 glm::vec4(m_specular.r, m_specular.g, m_specular.b, 0.0f),
                                                                 memory_offset + 4 * sizeof(glm::vec4), sizeof(glm::vec4));
}

std::vector<SpotLight> SpotLight::light_lists;

} // namespace SHM
