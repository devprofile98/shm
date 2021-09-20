cmake_minimum_required(VERSION 3.14)

project(SHM VERSION 0.1)

set (CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(shm_src 
#    F:/project/SHM/PlayGround/world.cpp
#    F:/project/SHM/PlayGround/gpc.cpp
    F:/project/SHM/PlayGround/flappybird.cpp
    source/glad.c
    source/Engine.cpp
    source/context_manager.cpp
    source/Handler.cpp
    source/Camera.cpp
    source/Light.cpp

)

set(opengl_renderer_src
    openGLRenderer/openGLRenderer.cpp
    openGLRenderer/Model.cpp
    openGLRenderer/Mesh.cpp
    openGLRenderer/shader.cpp
    openGLRenderer/buffers.cpp
    openGLRenderer/openglutility.cpp
    openGLRenderer/texture.cpp

)

set(cyclon_src
    ../shm-physics/src/particle.cpp
    ../shm-physics/src/pfgen.cpp
    ../shm-physics/src/plinks.cpp
    ../shm-physics/src/pcontacts.cpp
)

set(physic_src
    ../cyclone-physics/src/body.cpp
    ../cyclone-physics/src/collide_coarse.cpp
    ../cyclone-physics/src/collide_fine.cpp
    ../cyclone-physics/src/contacts.cpp
    ../cyclone-physics/src/core.cpp
    ../cyclone-physics/src/fgen.cpp
    ../cyclone-physics/src/joints.cpp
    ../cyclone-physics/src/particle.cpp
    ../cyclone-physics/src/pcontacts.cpp
    ../cyclone-physics/src/pfgen.cpp
    ../cyclone-physics/src/plinks.cpp
    ../cyclone-physics/src/pworld.cpp
    ../cyclone-physics/src/random.cpp
    ../cyclone-physics/src/world.cpp
)


add_subdirectory(include/shys)
add_library(shm-engine SHARED ${opengl_renderer_src} ${shm_src} ${cyclon_src} ${physic_src} )
target_link_libraries(shm-engine shys)
if (WIN32)
    target_link_libraries(shm-engine "F:/project/SHM/Engine/include/GLFW/glfw3.lib")
    target_link_libraries(shm-engine "F:/project/SHM/Engine/include/assimp/assimp-vc142-mtd.lib")
    
elseif(UNIX)
    target_link_libraries(shm-engine glfw3)
    target_link_libraries(shm-engine assimp)
endif()

target_include_directories(shm-engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/openGLRenderer/)
target_include_directories(shm-engine PUBLIC include/ ../shm-physics/include/cyclon/ ../cyclone-physics/include/)

