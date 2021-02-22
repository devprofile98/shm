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

)

set(opengl_renderer_src
    openGLRenderer/openGLRenderer.cpp
    openGLRenderer/Model.cpp
    openGLRenderer/Mesh.cpp
    openGLRenderer/shader.cpp

)

add_library(shm-engine SHARED ${opengl_renderer_src} ${shm_src} )

if (WIN32)
    message("****" ${CMAKE_CURRENT_SOURCE_DIR}/include/GLFW/glfw3.lib)
    target_link_libraries(shm-engine "F:/project/SHM/Engine/include/GLFW/glfw3.lib")
    target_link_libraries(shm-engine "F:/project/SHM/Engine/include/assimp/assimp-vc142-mtd.lib")
    
elseif(UNIX)
    target_link_libraries(shm-engine glfw3)
    target_link_libraries(shm-engine assimp)
endif()

target_include_directories(shm-engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/openGLRenderer/)
target_include_directories(shm-engine PUBLIC include/)
