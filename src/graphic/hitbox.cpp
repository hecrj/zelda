#include "hitbox.hpp"

Hitbox::Hitbox(float x, float y, float width, float height) :
        super(x, y, width, height)
{}

bool Hitbox::CollidesWith(Rectangle *r) const {
    if(!super::CollidesWith(r))
        return false;

    // TODO: Pixel perfect colisions
    return true;
}
