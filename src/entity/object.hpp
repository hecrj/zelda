#pragma once

#include "../entity.hpp"
#include "../map/tileset.hpp"

class Object : public Entity {
public:
    typedef Entity super;
    Object(Sprite* sprite, float x, float y);

    Sprite* CurrentSprite(vec2f& sprite_position) const;
    Sprite* CurrentSprite() const;

    void Render() const;

private:
    Sprite* sprite_;
};
