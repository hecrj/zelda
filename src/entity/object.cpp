#include "object.hpp"

Object::Object(Sprite* sprite, float x, float y) :
        super(x, y, sprite->width(), sprite->height()),
        sprite_(sprite),
        offset_(vec2f(0, 0))
{}

Object::Object(Sprite* sprite, float x, float y, const vec2f& offset) :
        super(x, y, sprite->width() + offset.x, sprite->height() + offset.y),
        sprite_(sprite),
        offset_(offset)
{}

void Object::Draw() const {
    sprite_->Render(position_ + offset_);
}

Sprite* Object::CurrentSprite(vec2f &sprite_position) const {
    return sprite_;
}

Sprite* Object::CurrentSprite() const {
    return sprite_;
}

bool Object::IsVulnerable() const {
    return true;
}
