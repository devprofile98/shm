cmake_minimum_required(VERSION 3.14)

project(shm)
add_subdirectory(Engine)

# add_custom_target(install_engine
#     COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target install
#     WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/Engine
# )

add_subdirectory(examples/basic-scene)

# add_dependencies(shm-engine install_engine)

