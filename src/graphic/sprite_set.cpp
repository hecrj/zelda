#include <iostream>
#include "sprite_set.hpp"

SpriteSet::SpriteSet(const std::vector<Sprite*>& sprites, int idle_index, int interval, vec2f position) :
        sprites(sprites),
        width(0),
        height(0),
        position(position),
        idle_index(idle_index),
        interval(interval),
        ping_pong(false)
{
    for(Sprite* sprite : sprites) {
        if(sprite->width() > width)
            width = sprite->width();

        if(sprite->height() > height)
            height = sprite->height();
    }
}

SpriteSet::SpriteSet(const std::vector<Sprite*>& sprites, int idle_index, int interval) :
        SpriteSet(sprites, idle_index, interval, vec2f(0, 0))
{}
