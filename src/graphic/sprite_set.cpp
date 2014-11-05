#ifdef _WIN32
#include <Windows.h>
#endif
#include <iostream>
#include "sprite_set.hpp"

SpriteSet::SpriteSet(const std::vector<Sprite*>& sprites, int idle_index, int interval, const vec2f& position) :
        sprites(sprites),
        width(0),
        height(0),
        position(position),
        idle_index(idle_index),
        ping_pong(false)
{
    for(Sprite* sprite : sprites) {
        if(sprite->width() > width)
            width = sprite->width();

        if(sprite->height() > height)
            height = sprite->height();

        intervals.push_back(interval);
    }
}

SpriteSet::SpriteSet(const std::vector<Sprite*>& sprites, int idle_index, vec2f const& position,
        const std::vector<int>& intervals) :
        SpriteSet(sprites, idle_index, 0, position)
{
    this->intervals = intervals;
}
