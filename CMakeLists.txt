
cmake_minimum_required(VERSION 2.8.4)
project(VirtualVista)
set(EXECUTABLE_FILE "VirtualVista")

if(NOT CMAKE_BUILD_TYPE)
  message(STATUS "Build type defaulting to \"Release\"")
  set(CMAKE_BUILD_TYPE "Release")
endif()

if(APPLE)
	set(CMAKE_CXX_COMPILER "/usr/bin/g++")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo")
endif()

# Defines where all source code goes.
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
# Defines where all shader files go.
set(SHADER_DIR ${SRC_DIR}/shaders)

# Checks if build directory exists, if not, then create one at build time.
if(NOT EXISTS "${CMAKE_SOURCE_DIR}/build/")
	execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/build/)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build")

# Sets the cmake directory for finding dependencies.
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

####### Dependencies
set(DEPS ${CMAKE_SOURCE_DIR}/deps)
find_package(GLM REQUIRED)
add_subdirectory(${DEPS}/glfw)
include_directories(${DEPS}/glfw/include)

# Setting files necessary for compilation.
set(SOURCE_FILES ${SRC_DIR}/main.cpp
                 ${SRC_DIR}/glew.cpp
                 ${SRC_DIR}/Shader.cpp
                 ${SRC_DIR}/Utilities.cpp)
                 #${SRC_DIR}/Renderer.cpp
                 #${SRC_DIR}/PolyManager.cpp
                 #${SRC_DIR}/Application.cpp)

add_executable(${EXECUTABLE_FILE} ${SOURCE_FILES})
target_link_libraries(${EXECUTABLE_FILE} glfw ${GLFW_LIBRARIES})
