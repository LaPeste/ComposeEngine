cmake_minimum_required (VERSION 3.10.2)

#set(CMAKE_CXX_COMPILER "/usr/bin/g++-7.4.0")
set(CMAKE_BUILD_TYPE Debug)

# set project name
project (ComposeEngine VERSION 0.1)

# set C++ standard version
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "-fpermissive")

# build the dependency project (sfml-tmxloader)
execute_process(COMMAND ${CMAKE_COMMAND} ${PROJECT_SOURCE_DIR}/sfml-tmxloader)
execute_process(COMMAND ${CMAKE_COMMAND} --build ${PROJECT_SOURCE_DIR}/sfml-tmxloader)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  ${PROJECT_SOURCE_DIR}/EngineConfig.h.in
  ${PROJECT_BINARY_DIR}/include/EngineConfig.h
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

link_directories(${PROJECT_SOURCE_DIR}/lib)

add_subdirectory(${PROJECT_SOURCE_DIR}/src/AI)

set(EXECUTABLE_NAME "MarioClone")

# Define sources and executable
file(GLOB_RECURSE SOURCES src/*.cpp)
add_executable(${EXECUTABLE_NAME} ${SOURCES})

target_include_directories(
  ${EXECUTABLE_NAME} PUBLIC
  ${PROJECT_SOURCE_DIR}/include/
  ${PROJECT_SOURCE_DIR}/sfml-tmxloader/include
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

install (TARGETS ${EXECUTABLE_NAME} DESTINATION GameTest)
install (FILES ${PROJECT_BINARY_DIR}/EngineConfig.h DESTINATION include)
