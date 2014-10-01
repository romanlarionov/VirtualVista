
cmake_minimum_required(VERSION 2.8.4)
project(Test)

SET(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++")

####### Dependencies
SET(DEPS /deps)

SET(GLFW_ROOT_DIR ${DEPS}/GLFW)
add_subdirectory(${GLFW_ROOT_DIR})
include_directories(${GLFW_ROOT_DIR}/include)

IF (APPLE)
	find_package(OpenGL REQUIRED)
	include_directories(${OPENGL_INCLUDE_DIR})

	INCLUDE_DIRECTORIES(/System/Library/Frameworks)
	FIND_LIBRARY(OpenGL_LIBRARY OpenGL)
	MARK_AS_ADVANCED(OpenGL_LIBRARY)
	SET(EXTRA_LIBS ${OpenGL_LIBRARY})


ENDIF (APPLE)

set(SOURCE_FILES main.cpp shader.frag shader.vert)
add_executable(Test ${SOURCE_FILES})