cmake_minimum_required(VERSION 2.8.4)
project(zelda)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    src/game.cpp
    src/game.h
    src/main.cpp
    src/scene.cpp
    src/scene.h
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

target_link_libraries(zelda
    ${OPENGL_LIBRARIES}
    ${GLUT_LIBRARY}
    # TODO: Get rid of the nvidia library?
    -L/usr/lib/nvidia-331/
)
