cmake_minimum_required(VERSION 2.8.4)
project(zelda)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    game.cpp
    game.h
    main.cpp
    scene.cpp
    scene.h
    utils.h
    utils.cpp)

add_executable(zelda ${SOURCE_FILES})

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

target_link_libraries(zelda ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
