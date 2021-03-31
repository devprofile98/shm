#ifndef SHM_BASE_UTILITY_H
#define SHM_BASE_UTILITY_H

#include <Core.hpp>
#include <buffers.hpp>

#include <iostream>

namespace SHM {

    // -------------------------
    // this class is an Abstract container for common functionallity
    // needed by SHM renderer's, such as :
    // 1- functions that use GPU api to upload or manipulate data
    // 2-
    // -------------------------

    class SHM_EXPORT BaseUtility{
    public:
        BaseUtility(){};
        virtual ~BaseUtility(){};

        // -------------------------
        //  InitWorld function is responsible for
        //  configuring and setting any default value
        //  needed for initial scene such as:
        //  * world default objects
        //  * lighting values : Structure's and respective UBO's
        //  ....
        // -------------------------
        virtual void InitWorld() = 0;
    };

}

#endif // SHM_BASE_UTILITY_H
