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
    # source/Logger.cpp
    # this files are for the internal use of the engine
    internal/CameraActor.cpp
)

set(opengl_renderer_src
    openGLRenderer/openGLRenderer.cpp
    openGLRenderer/Model.cpp
    openGLRenderer/Mesh.cpp
    openGLRenderer/shader.cpp
    openGLRenderer/buffers.cpp
    openGLRenderer/openglutility.cpp
    openGLRenderer/texture.cpp
    openGLRenderer/CubeMaps.cpp
)
set(physic_src
    include/physics/BasePhysics.cpp
    include/physics/WorldObject.cpp
    include/physics/PhysicWorld.cpp
)

add_library(shm-engine SHARED ${opengl_renderer_src} ${shm_src} ${physic_src} )
target_link_libraries(shm-engine ${CMAKE_DL_LIBS})
# target_compile_options(shm-engine PRIVATE -g)


if (WIN32)
    # make sure that the paths point to the right files
    target_link_libraries(shm-engine "${CMAKE_CURRENT_SOURCE_DIR}/include/GLFW/glfw3.lib")
    target_link_libraries(shm-engine "${CMAKE_CURRENT_SOURCE_DIR}/include/assimp-vc142-mt.lib")
    
elseif(UNIX)
    target_link_libraries(shm-engine glfw3 X11)
    target_link_libraries(shm-engine assimp)
    target_link_libraries(shm-engine spdlog)
endif()
    
target_include_directories(
        shm-engine PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/openGLRenderer/
        include/assimp/include/
        include/assimp/build/x64/include
        include/spdlog/include/
        include/
        internal/
)

