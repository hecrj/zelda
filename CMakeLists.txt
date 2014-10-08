cmake_minimum_required(VERSION 2.8.4)
project(zelda)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    src/game.cpp
    src/game.h
    src/main.cpp
    src/map.cpp
    src/map.h
    src/utils.h
    src/utils.cpp
    lib/TMXParser/src/TMXParser.cpp
    lib/TSXParser/src/TSXParser.cpp
)

add_executable(zelda ${SOURCE_FILES})

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories(
    ${OPENGL_INCLUDE_DIRS}
    ${GLUT_INCLUDE_DIRS}
    lib/TMXParser/include
    lib/TSXParser/include
)

set(NVIDIA_LIB)

# TODO: Improve NVIDIA detection
if(EXISTS /usr/lib/nvidia-331)
set(NVIDIA_LIB -L/usr/lib/nvidia-331/)
endif()

target_link_libraries(zelda
    ${OPENGL_LIBRARIES}
    ${GLUT_LIBRARY}
    ${NVIDIA_LIB}
)
