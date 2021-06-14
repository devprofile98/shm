#ifndef SHM_LIGHT_H
#define SHM_LIGHT_H

#include <stdint.h>
#include "Common.hpp"
#include "Engine.hpp"

namespace SHM {

    // base class for all type of Ligth
    class Light{
        public:
            Light();
            ~Light();

            void setAmbient(const Color& color);
            void setSpecular(const Color& color);
            void setDiffuse(const Color& color);

            virtual void ambientChanged()=0;
            virtual void specularChanged()=0;
            virtual void diffuseChanged()=0;

        protected:
            Color m_ambient;
            Color m_specular;
            Color m_diffuse;
            uint32_t light_index;

            uint32_t memory_offset = 0;
        };

    // represent a Directional light
    class DirectionalLight: public Light{
        public:
        DirectionalLight(float x=0, float y=0, float z=0);
        DirectionalLight(const Vector3& direction);
        ~DirectionalLight();
        Vector3 direction;

        void ambientChanged() override;
        void diffuseChanged() override;
        void specularChanged() override;
    };

    // represent a Point Light
    class PointLight: public Light{
    public:
        PointLight(float x=0, float y=0, float z=0);
        PointLight(const Vector3& position);
        ~PointLight();
        Vector3 position;

        void ambientChanged() override;
        void diffuseChanged() override;
        void specularChanged() override;
    };

    // represent a Spot Light

    class SpotLight: public Light{
    public:
//        SpotLight(const Vector3& direction, const Vector3& position);
        SpotLight(
                const Vector3& direction,
                const Vector3& position,
                const Color& diffuse = {1.0f, 0.0f,0.0f},
                const Color& specular = {0.92, 0.55, 0.1},
                const Color& ambient = {0.72f,0.72f ,0.72f}
                );
        ~SpotLight();
        Vector3 direction, position;
        void setDiffuse1(const Color& color);

        void ambientChanged() override;
        void diffuseChanged() override;
        void specularChanged() override;

         enum class member_offset{
            position = 0,
            direction = 16,

            ambient = 32,
            diffuse = 48,
            specular = 64,

             constant = 80,
             linear = 84,
             quadratic = 88,
             cutOff = 92,
             outerCutOff  = 96
        };
    private:
         static std::vector<SpotLight> light_lists;
    };
}


#endif //SHM_LIGHT_H
