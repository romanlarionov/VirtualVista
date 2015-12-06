cmake_minimum_required(VERSION 3.0)
project(VirtualVista)

option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(deps/glfw)

option(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
option(ASSIMP_BUILD_SAMPLES OFF)
option(ASSIMP_BUILD_TESTS OFF)
add_subdirectory(deps/assimp)

ADD_SUBDIRECTORY(deps/Simple-OpenGL-Image-Library)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++11")
    if(NOT WIN32)
        set(GLAD_LIBRARIES dl)
    endif()
endif()

if(NOT EXISTS "${CMAKE_SOURCE_DIR}/build/")
  execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/build/)
endif()

include_directories("include/"
                    "deps/assimp/include/"
                    "deps/glad/include/"
                    "deps/glfw/include/"
                    "deps/glm/"
                    "deps/Simple-OpenGL-Image-Library/src/")

file(GLOB DEPS_SOURCES deps/glad/src/glad.c)
file(GLOB PROJECT_HEADERS include/vv/*.h)
file(GLOB PROJECT_SOURCES src/*.cpp)
file(GLOB PROJECT_SHADERS src/shaders/*.comp
                          src/shaders/*.frag
                          src/shaders/*.geom
                          src/shaders/*.vert)

file(GLOB PROJECT_CONFIGS "CMakeLists.txt"
                          "README.md"
                          ".gitignore"
                          ".gitmodules")

source_group("include" FILES ${PROJECT_HEADERS})
source_group("shaders" FILES ${PROJECT_SHADERS})
source_group("src" FILES ${PROJECT_SOURCES})
source_group("deps" FILES ${DEPS_SOURCES})

add_definitions(-DGLFW_INCLUDE_NONE -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES}
                               ${PROJECT_HEADERS}
                               ${PROJECT_SHADERS}
                               ${PROJECT_CONFIGS}
                               ${DEPS_SOURCES})

target_link_libraries(${PROJECT_NAME} assimp glfw SOIL ${SOIL_LIBRARIES} ${GLFW_LIBRARIES})

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build")
