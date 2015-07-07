
cmake_minimum_required(VERSION 2.8.4)
project(VirtualVista)
set(VV_EXECUTABLE_FILE "VirtualVista")

if(NOT CMAKE_BUILD_TYPE)
  message(STATUS "Build type defaulting to \"Debug\"")
  set(CMAKE_BUILD_TYPE "Debug")
endif()

######################################################## OS Specific
if(UNIX) # OS X included
    set(CMAKE_CXX_COMPILER "/usr/bin/g++")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

if(APPLE)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo")
endif()

######################################################## Generation
if(NOT EXISTS "${CMAKE_SOURCE_DIR}/build/")
	execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/build/)
endif()

######################################################## Defines
# Defines where all source files go.
set(VV_SRC_DIR ${CMAKE_SOURCE_DIR}/src)

# Defines where all header files go.
set(VV_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

# Defines where all dependecies go.
set(VV_DEPS_DIR ${CMAKE_SOURCE_DIR}/deps)

# So cmake knows where to put the executable and helper files.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build")

# So cmake can use the FindXXX.cmake files for dependecies.
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

######################################################## Dependencies
# GLEW
set(GLEW_LOCATION "${VV_DEPS_DIR}/glew")
find_package(GLEW REQUIRED)

# GLM
find_package(GLM REQUIRED)

# GLFW
add_subdirectory(${VV_DEPS_DIR}/glfw)
include_directories(${VV_DEPS_DIR}/glfw/include)

# ASSIMP
find_package(assimp REQUIRED)

# SOIL
find_package(SOIL REQUIRED)

######################################################## Linking
include_directories(${VV_INCLUDE_DIR})

# Setting files necessary for compilation.
set(VV_SOURCE_FILES ${VV_SRC_DIR}/main.cpp
                 ${VV_SRC_DIR}/AppManager.cpp
                 ${VV_SRC_DIR}/Application.cpp
                 ${VV_SRC_DIR}/Input.cpp
                 ${VV_SRC_DIR}/Shader.cpp
                 ${VV_SRC_DIR}/Camera.cpp
                 ${VV_SRC_DIR}/Mesh.cpp
                 ${VV_SRC_DIR}/Settings.cpp)

add_executable(${VV_EXECUTABLE_FILE} ${VV_SOURCE_FILES})
target_link_libraries(${VV_EXECUTABLE_FILE} glfw ${GLFW_LIBRARIES} ${GLEW_LIBRARY})
