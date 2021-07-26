# shm
My 3D Engine

# BUILD on debian
* install assimp 
> sudo apt install libassimp-dev assimp-utils
* install glfw3
> sudo apt install libglfw3 libglfw3-dev

## Build from source
in source directory run below command

> mkdir build && cd build

> cmake ..

> make or (on windows) use cmake --build . or your make tool

an executable file "playground" is generated, run it with 
> ./playground
