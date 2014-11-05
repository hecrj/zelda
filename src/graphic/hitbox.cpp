#ifdef _WIN32
#include <Windows.h>
#endif
#include "hitbox.hpp"

Hitbox::Hitbox(float x, float y, float width, float height) :
        super(x, y, width, height)
{}

bool Hitbox::IsHitbox() const {
    return true;
}
