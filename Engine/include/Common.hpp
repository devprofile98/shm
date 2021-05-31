#ifndef SHM_COMMON_H
#define SHM_COMMON_H

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>


namespace SHM {
    struct Color{
        Color(){};
        Color(float red, float green, float blue):r(red), g(green), b(blue)
        {
            normalize();
//            std::cout << "normalized colors are"
        }
        float r, g, b;

        // call this function if values are in range 0-255
        void normalize(){
            if (r >1 || g>1 || b>1){
                r = r/255.0f;
                g = g/255.0f;
                b = b/255.0f;
            }
        }
    };

    class Vector3{
    public:
        Vector3(float x=0, float y=0, float z=0):x(x), y(y), z(z)
        {
        }
        Vector3(const glm::vec3& vec):x(vec.x), y(vec.y), z(vec.z)
        {
            std::cout<< "VEctor3 is "<< vec.x <<" "<< vec.y << " "<< vec.z <<std::endl;
        }
        void set(float x, float y, float z){
            this->x = x;
            this->y = y;
            this->z = z;
        }

        float x, y, z;
    private:

    };
}


#endif
