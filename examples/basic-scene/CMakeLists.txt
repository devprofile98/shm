
cmake_minimum_required(VERSION 3.14)

project(test)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
file(GLOB Game_SRC CONFIGURE_DEPENDS "sources/*.cpp" "sources/*.c")

add_executable(
	test 
    ${Game_SRC}
)
# shm-physics/include/cyclon/ cyclone-physics/include/cyclone
target_include_directories(test PUBLIC includes/)
target_compile_options(test PUBLIC -g)

if (WIN32)
	target_link_libraries(test "F:/project/SHM/Engine/include/GLFW/glfw3.lib")
	target_link_libraries(test "F:/project/SHM/Engine/include/assimp/assimp-vc142-mtd.lib")

elseif(UNIX)
	target_link_libraries(test ${CMAKE_DL_LIBS})
	target_link_libraries(test Threads::Threads)
	target_link_libraries(test glfw3)
	target_link_libraries(test assimp)
	target_link_libraries(test X11)
endif()
target_link_libraries(test shm-engine)

# copy the asset folder to generated bin file
# so the asset folder can be used in the game
# and the path can be relative
add_custom_command(
	TARGET test 
	POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/assets ${CMAKE_BINARY_DIR}/bin/assets
)
message(${CMAKE_CURRENT_SOURCE_DIR}/assets)

