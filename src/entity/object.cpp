#include "object.hpp"

Object::Object(Sprite* sprite, float x, float y) :
        super(x, y, sprite->width(), sprite->height()),
        sprite_(sprite)
{}

void Object::Render() const {
    sprite_->Render(position_);
}

Sprite * Object::CurrentSprite(vec2f &sprite_position) const {
    return sprite_;
}

Sprite * Object::CurrentSprite() const {
    return sprite_;
}
