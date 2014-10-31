#pragma once

#include "../entity.hpp"
#include "../map/tileset.hpp"
#include "../map/level.hpp"

class Object : public Entity {
public:
    typedef Entity super;
    Object(Sprite* sprite, float x, float y);
    Object(Sprite* sprite, float x, float y, const vec2f& offset);

    bool IsVulnerable() const;
    Sprite* CurrentSprite(vec2f& sprite_position) const;
    Sprite* CurrentSprite() const;

    void Draw() const;

private:
    Sprite* sprite_;
    vec2f offset_;
};
