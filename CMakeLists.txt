
cmake_minimum_required(VERSION 2.8.4)
project(VirtualVista)
set(EXECUTABLE_FILE "VirtualVista.exe")

if(NOT CMAKE_BUILD_TYPE)
  message(STATUS "Build type defaulting to \"Release\"")
  set(CMAKE_BUILD_TYPE "Release")
endif()

if(UNIX OR APPLE)
	set(CMAKE_CXX_COMPILER "/usr/bin/g++")
	set(CMAKE_CXX_FLAGS "-std=c++11 -lglfw3")
endif()

if(APPLE)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo")
endif()

# Defines where all custom CMake scripts go.
set(CMAKE_SCRIPT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})
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
set(GLFW_ROOT_DIR ${DEPS}/glfw)
set(GLEW_ROOT_DIR ${DEPS}/glew)
set(GLM_ROOT_DIR ${DEPS}/glm)

find_package(GLM REQUIRED)
find_package(GLEW REQUIRED)
add_subdirectory(${GLFW_ROOT_DIR})

include_directories(${GLFW_INCLUDE_DIRS} 
                    ${GLEW_INCLUDE_DIRS}
					${GLM_INCLUDE_DIR})

# Setting files necessary for compilation.
set(HEADER_FILES ${SRC_DIR}/Utilities.h
                 ${SRC_DIR}/Renderer.h
                 ${SRC_DIR}/Poly.h
                 ${SRC_DIR}/PolyManager.h
                 ${SRC_DIR}/Application.h)

set(SOURCE_FILES ${SRC_DIR}/main.cpp
                 ${SRC_DIR}/Utilities.cpp
                 ${SRC_DIR}/Renderer.cpp
                 ${SRC_DIR}/Poly.cpp
                 ${SRC_DIR}/PolyManager.cpp
                 ${SRC_DIR}/Application.cpp)

set(RUNTIME_DEPS ${SHADER_DIR}/vertex.glsl
                 ${SHADER_DIR}/fragment.glsl)

add_executable(${EXECUTABLE_FILE} ${HEADER_FILES}
                                  ${SOURCE_FILES}
                                  ${RUNTIME_DEPS})

target_link_libraries(${EXECUTABLE_FILE} ${glfw_LIBRARIES}
                                         ${GLEW_LIBRARY})


