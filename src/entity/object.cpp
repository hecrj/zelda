#include "object.hpp"

Object::Object(Level* level, Sprite* sprite, float x, float y) :
        super(x, y, sprite->width(), sprite->height()),
        level_(level),
        sprite_(sprite)
{}

void Object::Draw() const {
    sprite_->Render(position_);
}

Sprite* Object::CurrentSprite(vec2f &sprite_position) const {
    return sprite_;
}

Sprite* Object::CurrentSprite() const {
    return sprite_;
}
