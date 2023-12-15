## A Scene with basic lighting using SHM
![alt text](./images/scene2.png?raw=true)

## Build [ linux ]
initialize the SHM submodule and build it:
```bash

git submodule update --init --recursive
cd Engine/Engine/
mkdir build && cd build
cmake .. && cmake --build . -j
cd ../../../
```

### build the Scene
```bash
mkdir build && cd build
cmake .. && cmake --build . -j10 && ./bin/test
```

> !Note: Make sure you have **Assimp** and **glfw** installed on your system. 


![alt SpotLight](./images/scene3.png?raw=true)
![alt text](./images/scene4.png?raw=true)
![alt text](./images/scene1.png?raw=true)
