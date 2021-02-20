cmake_minimum_required(VERSION 3.14)

project(PlayGround)
find_package (Threads)

set (CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_subdirectory(Engine)
add_executable(playground PlayGround/main.cpp )
target_include_directories(playground PUBLIC Engine/include/ Engine/openGLRenderer/)
target_link_libraries(playground shm-engine )
target_link_libraries(playground ${CMAKE_CURRENT_SOURCE_DIR}/Engine/include/GLFW/glfw3.lib)
target_link_libraries(playground ${CMAKE_CURRENT_SOURCE_DIR}/Engine/include/assimp/assimp-vc142-mtd.lib)
