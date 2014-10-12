cmake_minimum_required(VERSION 2.8.4)
project(zelda)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    src/game.cpp
    src/main.cpp
    src/map/tile_map.cpp
    src/map/level.cpp
    src/utils.cpp
    lib/TMXParser/src/tmx_map.cpp
    lib/TMXParser/src/xml_utils.cpp
    lib/TMXParser/src/tsx_tileset.cpp
)

add_executable(zelda ${SOURCE_FILES})

add_subdirectory(lib/soil)
add_subdirectory(lib/TMXParser)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(
    ${OPENGL_INCLUDE_DIRS}
    ${GLUT_INCLUDE_DIRS}
    ${SOIL_INCLUDE_DIRS}
    ${TMXPARSER_INCLUDE_DIRS}
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
    SOIL
    TMXParser
)
