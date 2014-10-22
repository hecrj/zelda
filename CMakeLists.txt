cmake_minimum_required(VERSION 2.8.4)
project(zelda)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    src/debug.cpp
    src/game.cpp
    src/main.cpp
    src/entity.cpp
    src/utils.cpp
    src/graphic/animation.cpp
    src/graphic/hitbox.cpp
    src/graphic/hitbox/animation_hitbox.cpp
    src/graphic/pixelmap.cpp
    src/graphic/sprite.cpp
    src/graphic/spritesheet.cpp
    src/graphic/sprite_set.cpp
    src/entity/mob.cpp
    src/entity/mob/link.cpp
    src/entity/mob/action.cpp
    src/entity/mob/action/move.cpp
    src/entity/mob/action/attack.cpp
    src/entity/mob/ai.cpp
    src/entity/mob/ai/player.cpp
    src/entity/mob/ai/wander.cpp
    src/map/tile_map.cpp
    src/map/level.cpp
    src/math/dir.cpp
    src/math/quadtree.cpp
    src/math/rectangle.cpp
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
if(EXISTS /usr/lib/nvidia-331-updates)
set(NVIDIA_LIB -L/usr/lib/nvidia-331-updates/)
endif()

target_link_libraries(zelda
    ${OPENGL_LIBRARIES}
    ${GLUT_LIBRARY}
    ${NVIDIA_LIB}
    SOIL
    TMXParser
)
