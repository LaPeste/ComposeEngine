cmake_minimum_required (VERSION 3.10.2)

set(CMAKE_BUILD_TYPE Debug)

project (ComposeEngine VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS -fpermissive)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
set(CMAKE_INSTALL_PREFIX $ENV{HOME}/MarioClone)

# extend path that the linker is gonna use to search for shared libraries
set(CMAKE_INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/lib)

# build the dependency project (sfml-tmxloader)
# Here ninja could be used, but I didn't want to bother
# checking if ninja is installed on the user's system.
# At the end of the day the tmx loader is expected to be modified extremely rarely
execute_process(COMMAND ${CMAKE_COMMAND} ${PROJECT_SOURCE_DIR}/sfml-tmxloader)
execute_process(COMMAND ${CMAKE_COMMAND} --build ${PROJECT_SOURCE_DIR}/sfml-tmxloader)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  ${PROJECT_SOURCE_DIR}/EngineConfig.h.in
  ${PROJECT_SOURCE_DIR}/include/EngineConfig.h
)

configure_file (
  ${PROJECT_SOURCE_DIR}/sfml-tmxloader/libpugi.so
  ${PROJECT_SOURCE_DIR}/lib
  COPYONLY
)

configure_file (
  ${PROJECT_SOURCE_DIR}/sfml-tmxloader/libtmx-loader.so
  ${PROJECT_SOURCE_DIR}/lib
  COPYONLY
)

# this applies recursively to all targets and libs, included children
include_directories(${PROJECT_SOURCE_DIR}/include/ ${PROJECT_SOURCE_DIR}/sfml-tmxloader/include)
link_directories(${PROJECT_SOURCE_DIR}/lib)

add_subdirectory(${PROJECT_SOURCE_DIR}/src/AI)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/Animations)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/Collisions)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/Components)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/DebugUtils)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/Entities)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/Events)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/GameExample)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/GameObjects)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/Systems)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/Utils)

set(EXECUTABLE_NAME MarioClone)

# Define sources and executable
# file(GLOB_RECURSE SOURCES src/*.cpp)
add_executable(${EXECUTABLE_NAME}
  src/main.cpp
  src/Camera.cpp
  src/ClassRegistry.cpp
  src/Constants.cpp
  src/Engine.cpp
  src/FPS.cpp
  src/MathLib.tpp
  src/SfmlInputEvent.cpp
  src/stdafx.cpp
  src/World.cpp
  $<TARGET_OBJECTS:BehaviourTree> 
  $<TARGET_OBJECTS:Animations>
  $<TARGET_OBJECTS:Collisions>
  $<TARGET_OBJECTS:Components>
  $<TARGET_OBJECTS:DebugUtils>
  $<TARGET_OBJECTS:Entities>
  $<TARGET_OBJECTS:Events>
  $<TARGET_OBJECTS:GameExample>
  $<TARGET_OBJECTS:GameExample_AI>
  $<TARGET_OBJECTS:GameExample_Behaviours>
  $<TARGET_OBJECTS:GameExample_GameObjects>
  $<TARGET_OBJECTS:GameObjects>
  $<TARGET_OBJECTS:Systems>
  $<TARGET_OBJECTS:Utils>
)

  find_package(SFML 2.5 COMPONENTS network audio graphics window system REQUIRED)
target_link_libraries(
  ${EXECUTABLE_NAME} PUBLIC
  sfml-network
  sfml-audio
  sfml-graphics
  sfml-window
  sfml-system
  pugi
  tmx-loader
)

install (TARGETS ${EXECUTABLE_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX})
install (DIRECTORY ${PROJECT_BINARY_DIR}/lib/ DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
install (DIRECTORY ${PROJECT_BINARY_DIR}/resources/ DESTINATION ${CMAKE_INSTALL_PREFIX}/resources)
