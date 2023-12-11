# SHM: My 3D Engine

![alt text](https://github.com/devprofile98/shm-scene1/blob/main/images/scene2.png?raw=true) 

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
