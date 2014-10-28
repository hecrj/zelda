#pragma once

#include "../entity.hpp"
#include "../map/tileset.hpp"
#include "../map/level.hpp"

class Object : public Entity {
public:
    typedef Entity super;
    Object(Level* level, Sprite* sprite, float x, float y);

    Sprite* CurrentSprite(vec2f& sprite_position) const;
    Sprite* CurrentSprite() const;

    void Draw() const;

protected:
    Level* level_;

private:
    Sprite* sprite_;
};
