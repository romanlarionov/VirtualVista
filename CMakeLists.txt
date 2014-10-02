
cmake_minimum_required(VERSION 2.8.4)
project(Test)

#SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")

SET(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
SET(SHADER_DIR ${SRC_DIR}/shaders)

if (APPLE)
	set(SOURCE_FILES ${SRC_DIR}/main.cpp ${SHADER_DIR}/shader.frag ${SHADER_DIR}/shader.vert)
	add_executable(Test ${SOURCE_FILES})
ENDIF (APPLE)

####### Dependencies
SET(DEPS ${CMAKE_SOURCE_DIR}/deps)

# GLFW
SET(GLFW_ROOT_DIR ${DEPS}/GLFW)
add_subdirectory(${GLFW_ROOT_DIR})
include_directories(${GLFW_SOURCE_DIR}/include)
target_link_libraries(Test glfw ${glfw_LIBRARIES})

