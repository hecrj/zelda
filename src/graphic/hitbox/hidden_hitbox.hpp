#pragma once

#include "../hitbox.hpp"
#include "../animation.hpp"

class HiddenHitbox : public Hitbox {
public:
    typedef Hitbox super;
    HiddenHitbox(float x, float y, Animation* animation);

    Hitmap* GetHitmap() const;

private:
    Animation* animation_;
};
