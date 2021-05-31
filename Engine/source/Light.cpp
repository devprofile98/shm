#include "Light.hpp"

namespace SHM {
    Light::Light(){

    }
    Light::~Light(){

    }

    void Light::setAmbient(const Color &color)
    {
        m_ambient = color;
    }

    void Light::setSpecular(const Color &color)
    {
        m_specular = color;
    }

    void Light::setDiffuse(const Color &color)
    {
        m_diffuse = color;
    }

    DirectionalLight::DirectionalLight(float x, float y, float z):
        direction(Vector3(x, y, z))
    {

    }

    DirectionalLight::DirectionalLight(const Vector3 &direction):
        direction(direction)
    {

    }

    DirectionalLight::~DirectionalLight()
    {

    }

    PointLight::PointLight(float x, float y, float z):
        position(Vector3(x, y, z))
    {

    }

    PointLight::PointLight(const Vector3 &position):
        position(position)
    {

    }

    PointLight::~PointLight()
    {

    }

    SpotLight::SpotLight(const Vector3 &direction, const Vector3 &position):
        direction(direction), position(position)
    {
        if (light_lists.size() > 12){
            std::cout << "Lights are full"<<std::endl;
            return;
        }
        int offset = light_lists.size()* (7*sizeof (glm::vec4));
        setAmbient(Color(0.72f,0.72f ,0.72f));
        setDiffuse(Color(0.92, 0.0, 0.0));
        setSpecular(Color(0.92, 0.55, 0.1));
        std::cout<<"in spot light class -------"<<std::endl;
        Engine::getRenderer()->GetUtility()->uploadVec4(
                    Engine::getRenderer()->ubo_spots,
                    glm::vec4(position.x, position.y, position.z, 0.0f),
                    offset + int(member_offset::position),
                    sizeof(glm::vec4)
                    );

        Engine::getRenderer()->GetUtility()->uploadVec4(
                    Engine::getRenderer()->ubo_spots,
                    glm::vec4(direction.x, direction.y, direction.z, 0.0f),
                    offset + sizeof(glm::vec4),
                    sizeof(glm::vec4)
                    );

        Engine::getRenderer()->GetUtility()->uploadVec4(
                    Engine::getRenderer()->ubo_spots,
                    glm::vec4(m_ambient.r, m_ambient.g, m_ambient.b, 0.0f),
                    offset + 2*sizeof(glm::vec4),
                    sizeof(glm::vec4)
                    );

        Engine::getRenderer()->GetUtility()->uploadVec4(
                    Engine::getRenderer()->ubo_spots,
                    glm::vec4(m_diffuse.r, m_diffuse.g, m_diffuse.b, 0.0f),
                    offset + 3*sizeof(glm::vec4),
                    sizeof(glm::vec4)
                    );


        Engine::getRenderer()->GetUtility()->uploadVec4(
                    Engine::getRenderer()->ubo_spots,
                    glm::vec4(m_specular.r, m_specular.g, m_specular.b, 0.0f),
                    offset + 4*sizeof(glm::vec4),
                    sizeof(glm::vec4)
                    );

        Engine::getRenderer()->GetUtility()->uploadFloat(
                    Engine::getRenderer()->ubo_spots,
                    1.0f,
                    offset + 5*sizeof(glm::vec4),
                    sizeof(float)
                    );


        Engine::getRenderer()->GetUtility()->uploadFloat(
                    Engine::getRenderer()->ubo_spots,
                    0.35f,
                    offset + 5*sizeof(glm::vec4)+4,
                    sizeof(float)
                    );


        Engine::getRenderer()->GetUtility()->uploadFloat(
                    Engine::getRenderer()->ubo_spots,
                    0.44f,
                    offset + 5*sizeof(glm::vec4)+8,
                    sizeof(float)
                    );


        Engine::getRenderer()->GetUtility()->uploadFloat(
                    Engine::getRenderer()->ubo_spots,
                    glm::cos(glm::radians(12.5f)),
                    offset + 5*sizeof(glm::vec4)+12,
                    sizeof(float)
                    );

        Engine::getRenderer()->GetUtility()->uploadFloat(
                    Engine::getRenderer()->ubo_spots,
                    glm::cos(glm::radians(17.5f)),
                    offset + 6*sizeof(glm::vec4),
                    sizeof(float)
                    );

        light_lists.push_back(*this);
        std::cout << light_lists.size()<<std::endl;
        std::cout<<"in spot light class +++++++++"<<std::endl;

    }

    SpotLight::~SpotLight()
    {

    }

    void SpotLight::setDiffuse1(const Color &color)
    {
        m_diffuse = color;
        std::cout<< color.r <<color.g <<color.b<<" "<<int(member_offset::ambient)<<std::endl;
        Engine::getRenderer()->GetUtility()->uploadVec4(
                    Engine::getRenderer()->ubo_spots,
                    glm::vec4(color.r, color.g, color.b, 0.0f),
                    light_lists.size()* (7*sizeof (glm::vec4)) + int(member_offset::diffuse),
                    sizeof(glm::vec4)
                    );
    }

    std::vector<SpotLight> SpotLight::light_lists;

}
