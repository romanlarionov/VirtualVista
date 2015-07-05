
cmake_minimum_required(VERSION 2.8.4)
project(VirtualVista)
set(EXECUTABLE_FILE "VirtualVista")

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
# Checks if build directory exists, if not, then create one at build time.
if(NOT EXISTS "${CMAKE_SOURCE_DIR}/build/")
	execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/build/)
endif()

######################################################## Defines
# Defines where all source code goes.
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)

# Defines where all dependecies go.
set(DEPS ${CMAKE_SOURCE_DIR}/deps)

# So cmake knows where to put the executable and helper files.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build")

# So cmake can use the FindXXX.cmake files for dependecies.
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

######################################################## Dependencies
# GLEW
set(GLEW_LOCATION "${DEPS}/glew")
find_package(GLEW REQUIRED)

# GLM
find_package(GLM REQUIRED)

# GLFW
add_subdirectory(${DEPS}/glfw)
include_directories(${DEPS}/glfw/include)

######################################################## Linking
# Setting files necessary for compilation.
set(SOURCE_FILES ${SRC_DIR}/main.cpp
                 ${SRC_DIR}/AppManager.cpp
                 ${SRC_DIR}/Application.cpp
                 ${SRC_DIR}/Input.cpp
                 ${SRC_DIR}/Shader.cpp
                 ${SRC_DIR}/Camera.cpp)
                 #${SRC_DIR}/Utilities.cpp
                 #${SRC_DIR}/Renderer.cpp)

add_executable(${EXECUTABLE_FILE} ${SOURCE_FILES})
target_link_libraries(${EXECUTABLE_FILE} glfw ${GLFW_LIBRARIES} ${GLEW_LIBRARY})
