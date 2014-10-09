
cmake_minimum_required(VERSION 2.8.4)
project(Test)

if (NOT CMAKE_BUILD_TYPE)
  message(STATUS "Build type defaulting to \"Release\"")
  set(CMAKE_BUILD_TYPE "Release")
endif()

IF (APPLE)
	set(CMAKE_CXX_COMPILER "/usr/bin/cc")
	set(CMAKE_CXX_FLAGS "-lglfw3 -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo")
ENDIF (APPLE)

# Defines where all custom CMake scripts go.
set(CMAKE_SCRIPT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})
# Defines where all source code goes.
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
# Defines where all shader files go.
set(SHADER_DIR ${SRC_DIR}/shaders)

####### Dependencies
set(DEPS ${CMAKE_SOURCE_DIR}/deps)

# GLFW
set(GLFW_ROOT_DIR ${DEPS}/GLFW)
add_subdirectory(${GLFW_ROOT_DIR})

find_package(GLEW REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I/usr/include")

include_directories(${GLFW_INCLUDE_DIRS})


set(SOURCE_FILES    ${SRC_DIR}/main.cpp
					${SRC_DIR}/Scene.cpp
					${SRC_DIR}/Scene.h
					${SRC_DIR}/SimpleMeshObject.cpp
					${SRC_DIR}/SimpleMeshObject.h
					${SHADER_DIR}/shader.frag
					${SHADER_DIR}/shader.vert)

add_executable(Test ${SOURCE_FILES} )

target_link_libraries(Test ${glfw_LIBRARIES}
							${GLEW_LIBRARY})



