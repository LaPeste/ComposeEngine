cmake_minimum_required (VERSION 3.10.2)

#set(CMAKE_CXX_COMPILER "/usr/bin/g++-7.4.0")
set(CMAKE_BUILD_TYPE Debug)

# set project name
project (ComposeEngine)

# set project version number
set (Tutorial_VERSION_MAJOR 1)
set (Tutorial_VERSION_MINOR 0)

# set C++ standard version
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "-fpermissive")

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  ${PROJECT_SOURCE_DIR}/EngineConfig.h.in
  ${PROJECT_BINARY_DIR}/EngineConfig.h
  )

include_directories(${PROJECT_BINARY_DIR})


set(EXECUTABLE_NAME "MarioClone")
# set(SFML_include ${PROJECT_SOURCE_DIR}/lib/SFML/include/)
# set(tmx_include ${PROJECT_SOURCE_DIR}/lib/sfml-tmxLoader/include/)


########## SOURCES #################

# Define sources and executable
file(GLOB_RECURSE SOURCES src/*.cpp)
add_executable(${EXECUTABLE_NAME} ${SOURCES} src/main.cpp)

####################################


########## HEADERS #################
target_include_directories(${EXECUTABLE_NAME} PRIVATE
                            include
                            lib)


###################################

########### EXTERNAL LIBS ###########
find_package(SFML 2.5 COMPONENTS network audio graphics window system REQUIRED)
target_link_libraries(${EXECUTABLE_NAME} PRIVATE
                      sfml-network
                      sfml-audio
                      sfml-graphics
                      sfml-window
                      sfml-system
                      tmx-loader
                      pugi)


# target_link_libraries(${EXECUTABLE_NAME} PRIVATE
#                         ${PROJECT_SOURCE_DIR}/lib/sfml-tmxLoader/lib/libtmx-loader-s-d.a
#                         ${PROJECT_SOURCE_DIR}/lib/sfml-tmxLoader/lib/libpugi-s-d.a)




########## TARGETS #################

# add the install targets
install (TARGETS ${EXECUTABLE_NAME} DESTINATION GameTest)
install (FILES ${PROJECT_BINARY_DIR}/EngineConfig.h        
         DESTINATION include)

####################################
