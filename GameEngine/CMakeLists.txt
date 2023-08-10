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

link_directories(${PROJECT_SOURCE_DIR}/lib)

add_subdirectory(${PROJECT_SOURCE_DIR}/src/AI)

set(EXECUTABLE_NAME MarioClone)

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

install (TARGETS ${EXECUTABLE_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX})
install (DIRECTORY ${PROJECT_BINARY_DIR}/lib/ DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
install (DIRECTORY ${PROJECT_BINARY_DIR}/resources/ DESTINATION ${CMAKE_INSTALL_PREFIX}/resources)
