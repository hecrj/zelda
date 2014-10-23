#pragma once

#include "../entity.hpp"
#include "../map/tileset.hpp"

class MapObject : public Entity {
public:
    typedef Entity super;
    MapObject(Tileset* tileset, int gid, float x, float y, float width, float height);

    Sprite* CurrentSprite(vec2f& sprite_position) const;
    Sprite* CurrentSprite() const;

    void Render() const;

private:
    Tileset* tileset_;
    int gid_;
};
