cmake_minimum_required(VERSION 3.14)

project(SHM VERSION 0.1)

set(shm_src 
    source/glad.c
    source/Engine.cpp
    source/context_manager.cpp

)

set(opengl_renderer_src
    # openGLRenderer/glad.c
    openGLRenderer/openGLRenderer.cpp
    openGLRenderer/Model.cpp
    openGLRenderer/Mesh.cpp
    openGLRenderer/Camera.cpp
    openGLRenderer/shader.cpp

)


add_library(shm-engine SHARED ${opengl_renderer_src} ${shm_src} )
target_link_libraries(shm-engine ${CMAKE_CURRENT_SOURCE_DIR}/include/GLFW/glfw3.lib)
target_link_libraries(shm-engine ${CMAKE_CURRENT_SOURCE_DIR}/include/assimp/assimp-vc142-mtd.lib)
target_include_directories(shm-engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/openGLRenderer/)

target_include_directories(shm-engine PUBLIC include/)
# add_subdirectory(openGLRenderer)