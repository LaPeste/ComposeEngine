# ComposeEngine
-------------



## Copyrights

Andrea Catalini 2016-2023
Game Engine 2D - https://github.com/LaPeste/ComposeEngine

Zlib License:  
This software is provided 'as-is', without any express or  
implied warranty. In no event will the authors be held  
liable for any damages arising from the use of this software.  

Permission is granted to anyone to use this software for any purpose,  
including commercial applications, and to alter it and redistribute  
it freely, subject to the following restrictions:  

1. The origin of this software must not be misrepresented;  
   you must not claim that you wrote the original software.  
   If you use this software in a product, an acknowledgment  
   in the product documentation would be appreciated but  
   is not required.  

2. Altered source versions must be plainly marked as such,  
   and must not be misrepresented as being the original software.  

3. This notice may not be removed or altered from any  
   source distribution.


## Requirements
* Cmake 3.10
* SFML 2.x (http://sfml-dev.org)  
* Minimal C++14 compiler support (tested with VS14, clang-800.0.38 and g++ 13.2.0)


## Build and Run
1. From the root of the project go to the `GameEngine` folder:
   ```bash
   cd GameEngine
   ```
1. Fetch the submodules, which pulls `sfml-tmxloader`:
   ```bash
   git submodule update --init --recursive
   ```
1. configure cmake:
   ```bash
   cmake build .
   ```
1. build through cmake:
   ```bash
   cmake --build .
   ```
1. Run the executable:
   ```bash
   ./MarioClone
   ```