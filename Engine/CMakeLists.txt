cmake_minimum_required(VERSION 3.14)

project(SHM VERSION 0.1)

set (CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(shm_src 

    source/glad.c
    source/Engine.cpp
    source/context_manager.cpp
    source/Handler.cpp
    source/Camera.cpp
    source/Light.cpp
    source/Actor.cpp
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
    include/physics/BasePhysics.cpp
    include/physics/WorldObject.cpp
    include/physics/PhysicWorld.cpp

)

# add_subdirectory(include/shys)
add_library(shm-engine SHARED ${opengl_renderer_src} ${shm_src} ${cyclon_src} ${physic_src} )
target_link_libraries(shm-engine ${CMAKE_DL_LIBS})
target_compile_options(shm-engine PRIVATE -g)

if (WIN32)
    # make sure that the paths point to the right files
    target_link_libraries(shm-engine "F:/project/SHM/Engine/include/GLFW/glfw3.lib")
    target_link_libraries(shm-engine "F:/project/SHM/Engine/include/assimp/assimp-vc142-mtd.lib")
    
elseif(UNIX)
    target_link_libraries(shm-engine glfw3 X11)
    target_link_libraries(shm-engine assimp)
endif()

target_include_directories(shm-engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/openGLRenderer/)
target_include_directories(
    shm-engine PUBLIC 
    
    include/
    ../shm-physics/include/cyclon/
    ../cyclone-physics/include/
    )

