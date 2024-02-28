# SHM: My 3D Engine

![alt text](https://github.com/devprofile98/shm/blob/master/examples/basic-scene/images/scene1.png) 

## Build [ linux ]
initialize the SHM submodule and build it:
```bash

git clone https://github.com/devprofile98/shm.git
cd shm
git submodule update --init --recursive
cd Engine/
mkdir build && cd build
cmake .. && cmake --build . -j
```

use the generated library, for an example see [shm-scene1](https://github.com/devprofile98/shm-scene1.git)

![alt text](https://github.com/devprofile98/shm/blob/master/examples/basic-scene/images/scene2.png) 
![alt text](https://github.com/devprofile98/shm/blob/master/examples/basic-scene/images/scene3.png) 
![alt text](https://github.com/devprofile98/shm/blob/master/examples/basic-scene/images/scene4.png)
![alt text](https://github.com/devprofile98/shm/blob/master/examples/basic-scene/images/reflection.png)


