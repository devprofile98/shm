#ifndef SHM_COMMON_H
#define SHM_COMMON_H

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>


namespace SHM {
    /**
     represent a RGB color
     */
    struct Color{
        Color(){};
        Color(float red, float green, float blue):r(red), g(green), b(blue)
        {
            normalize();
        }
        float r, g, b;

        /** call normalize function if values are in range 0-255*/
        void normalize(){
            if (r >1 || g>1 || b>1){
                r = r/255.0f;
                g = g/255.0f;
                b = b/255.0f;
            }
        }
    };

    /** represent a basic 3D vector
     * use shm-physic Vector3 for more usage and support
    */

    class Vector3{
    public:
        Vector3(float x=0, float y=0, float z=0):x(x), y(y), z(z)
        {
        }
        Vector3(const glm::vec3& vec):x(vec.x), y(vec.y), z(vec.z)
        {
        }
        void set(float x, float y, float z){
            this->x = x;
            this->y = y;
            this->z = z;
        }

        float x, y, z;
    private:
    };

    /**
     * @brief linear interpolation between start to end by duration
     */
    class Lerp{
    public:
        Lerp(float* ref_value, float duration, float start, float end)
            :duration(duration), start(start), end(end), m_ref_value(ref_value)
        {
           step = (end - start) / duration;
        }


        float tick(){
            if ((*m_ref_value) + step < end){
                float temp = start;
                temp += step;
                start = temp;
                (*m_ref_value) += step;
                return temp;
            }
            return end;
        }

    private:
        float duration = 0;
        float step, start, end;
        float* m_ref_value;
    };


    class LerpManager{
    public:
        LerpManager() = delete;
        void add(Lerp p){
            wait_list.push_back(p);
        }
        static inline std::vector<Lerp> wait_list;
        static void exec(){
            for (Lerp& l: wait_list){
                l.tick();
            }
        };

    };
}


#endif
