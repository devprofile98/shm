#ifndef SHM_CORE_H
#define SHM_CORE_H


// rules on export and import 
#define MAKE_SHM_LIB
#if defined(SHM_STATIC)
    #define SHM_EXPORT 
#elif (defined(_WIN32) || defined(_WIN64))
    #ifdef  MAKE_SHM_LIB
        #define SHM_EXPORT __declspec(dllexport)
    #else
        #define SHM_EXPORT __declspec(dllimport)
    #endif  //MAKE_SHM_LIB
#elif defined(__GNUC__)
    #define SHM_EXPORT __attribute__ ((visibility("default")))
#else
    #define SHM_EXPORT 
#endif //SHM_STATIC


// include library header file

#include <glad/glad.h>
#include <GLFW/glfw3.h>
//gl math
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "shader.hpp"

// include common header files
#include "BaseRenderer.hpp"
//#include "BaseUtility.hpp"

// #include "openGLRenderer.hpp"
#include "context_manager.hpp"
// #include "Camera.hpp"




#endif  //SHM_CORE_H
