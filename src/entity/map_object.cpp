#include "map_object.hpp"

MapObject::MapObject(Sprite* sprite, float x, float y) :
        super(x, y, sprite->width(), sprite->height(), 1),
        sprite_(sprite)
{}

void MapObject::Render() const {
    sprite_->Render(position_);
}

Sprite *MapObject::CurrentSprite(vec2f &sprite_position) const {
    return sprite_;
}

Sprite *MapObject::CurrentSprite() const {
    return sprite_;
}
