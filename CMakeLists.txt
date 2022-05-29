cmake_minimum_required(VERSION 3.14)

project(PlayGround)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(Engine)
add_executable(playground PlayGround/main.cpp)
target_include_directories(playground PUBLIC Engine/include/ Engine/openGLRenderer/ shm-physics/include/cyclon/ cyclone-physics/include/cyclone)


if (WIN32)
	target_link_libraries(playground "F:/project/SHM/Engine/include/GLFW/glfw3.lib")
	target_link_libraries(playground "F:/project/SHM/Engine/include/assimp/assimp-vc142-mtd.lib")

elseif(UNIX)
	target_link_libraries(playground ${CMAKE_DL_LIBS})
	target_link_libraries(playground Threads::Threads)
	target_link_libraries(playground glfw3)
	target_link_libraries(playground assimp)
endif()
target_link_libraries(playground shm-engine)
