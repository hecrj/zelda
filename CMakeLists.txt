cmake_minimum_required(VERSION 2.8.4)
project(zelda)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    # Main files
    src/debug.cpp
    src/game.cpp
    src/hud.cpp
    src/main.cpp
    src/utils.cpp

    # Game screens
    src/screen.cpp
    src/screen/title_screen.cpp
    src/screen/level_screen.cpp
    src/screen/over_screen.cpp
    src/screen/win_screen.cpp

    # Audio
    src/audio/music.cpp
    src/audio/sound.cpp

    # Graphical stuff
    src/graphic/animation.cpp
    src/graphic/drawable.cpp
    src/graphic/font.cpp
    src/graphic/hitbox.cpp
    src/graphic/hitbox/animation_hitbox.cpp
    src/graphic/pixelmap.cpp
    src/graphic/sprite.cpp
    src/graphic/spritesheet.cpp
    src/graphic/sprite_set.cpp

    ## Graphic effects
    src/graphic/effect.cpp
    src/graphic/callback_effect.cpp
    src/graphic/effect/bounce.cpp
    src/graphic/effect/fade.cpp
    src/graphic/effect/float.cpp
    src/graphic/effect/rotation_fade.cpp
    src/graphic/effect/overlay.cpp
    src/graphic/effect/timer.cpp
    src/graphic/effect/menu.cpp
    src/graphic/effect/dialog.cpp
    src/graphic/effect/blink.cpp

    # Entities
    src/entity.cpp

    ## Mobs
    src/entity/mob.cpp
    src/entity/mob/link.cpp
    src/entity/mob/guard.cpp
    src/entity/mob/stalfos.cpp
    src/entity/mob/moldorm.cpp
    src/entity/mob/link_follower.cpp

    ### Mob actions
    src/entity/mob/action.cpp
    src/entity/mob/action/move.cpp
    src/entity/mob/action/attack.cpp
    src/entity/mob/action/push.cpp

    ### Mob AIs
    src/entity/mob/ai.cpp
    src/entity/mob/ai/chase.cpp
    src/entity/mob/ai/chase_evade.cpp
    src/entity/mob/ai/follower.cpp
    src/entity/mob/ai/player.cpp
    src/entity/mob/ai/wander.cpp
    src/entity/mob/ai/rotation_chase.cpp

    ## Objects
    src/entity/object.cpp
    src/entity/object/plant.cpp
    src/entity/object/pole_switch.cpp
    src/entity/object/pole.cpp

    ## Items
    src/entity/item.cpp
    src/entity/item/rupee.cpp
    src/entity/item/key.cpp

    ## Events
    src/entity/event.cpp
    src/entity/event/map_transition.cpp

    ## Doors
    src/entity/door.cpp
    src/entity/door/key_door.cpp
    src/entity/door/boss_door.cpp

    # Map
    src/map/tile_map.cpp
    src/map/tileset.cpp
    src/map/level.cpp
    src/map/location.cpp
    src/map/path.cpp
    src/map/level_events.cpp

    ## Level events
    src/map/events/intro.cpp
    src/map/events/dungeon_boss.cpp

    # Mathematical data structures
    src/math/dir.cpp
    src/math/quadtree.cpp
    src/math/rectangle.cpp
)

add_executable(zelda ${SOURCE_FILES})

add_subdirectory(lib/soil)
add_subdirectory(lib/TMXParser)
add_subdirectory(lib/sfml-audio)

if(WIN32)
SET(GLEW_INCLUDE_DIR lib/glew/include/)
SET(GLEW_LIBRARY lib/glew/lib/Release/Win32/glew32)
SET(GLUT_INCLUDE_DIR lib/glut/include/)
SET(GLUT_glut_LIBRARY lib/glut/lib/glut32)
endif()

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLUT REQUIRED)

include_directories(
    ${OPENGL_INCLUDE_DIRS}
	${GLEW_INCLUDE_DIRS}
    ${GLUT_INCLUDE_DIRS}
    ${SOIL_INCLUDE_DIRS}
    ${TMXPARSER_INCLUDE_DIRS}
    ${SFML_INCLUDE_DIRS}
)

set(NVIDIA_LIB)

# TODO: Improve NVIDIA detection
# If you have an NVIDIA card you would probably need to change this
# to the driver you are currently using
if(EXISTS /usr/lib/nvidia-331-updates)
set(NVIDIA_LIB -L/usr/lib/nvidia-331-updates/)
endif()

target_link_libraries(zelda
    ${OPENGL_LIBRARIES}
	${GLEW_LIBRARIES}
    ${GLUT_LIBRARY}
    ${NVIDIA_LIB}
    SOIL
    TMXParser
    sfml-audio
)
