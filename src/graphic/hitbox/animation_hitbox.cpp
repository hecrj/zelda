#include "animation_hitbox.hpp"
#include "../../debug.hpp"
#include <iostream>
#include <algorithm>

AnimationHitbox::AnimationHitbox(const vec2f& position, Animation* animation) :
        super(0, 0, animation->width(), animation->height())
{
    animation_ = animation;
    position_ = position + animation_->position();
}

Animation* AnimationHitbox::CurrentAnimation() const {
    return animation_;
}

Collision AnimationHitbox::CollisionType(Rectangle* rectangle) const {
    if(!rectangle->IsHitbox())
        return BLOCK;

    Hitbox* h = (Hitbox*) rectangle;
    Animation* a = h->CurrentAnimation();

    // Calculate rectangle intersection between h and a
    // This is necessary because the animation rectangle could be smaller than h
    const vec2f& hpos = h->position();
    const vec2f& apos = hpos + a->position();

    float x1f = std::max(hpos.x, apos.x);
    float y1f = std::max(hpos.y, apos.y);
    float x2f = std::min(hpos.x + h->width(), apos.x + a->width());
    float y2f = std::min(hpos.y + h->height(), apos.y + a->height());

    // Calculate the animation intersection
    x1f = std::max(position_.x, x1f);
    y1f = std::max(position_.y, y1f);
    int x2 = (int)(std::min(position_.x + width_, x2f) - position_.x);
    int y2 = (int)(std::min(position_.y + height_, y2f) - position_.y);

    int x1 = (int)(x1f - position_.x);
    int y1 = (int)(y1f - position_.y);

    int x_offset = (int)(position_.x - apos.x);
    int y_offset = (int)(position_.y - apos.y);

    const Pixelmap& h1 = *CurrentAnimation()->HitMap();
    const Pixelmap& h2 = *a->DamageMap();

    if(Debug::enabled) {
        h1.Print();
        h2.Print();

        // Print pixel collision info
        for(int i = y1; i < y2; ++i) {
            for(int j = x1; j < x2; ++j) {
                if(h1.map_[i][j] && h2.map_[i + y_offset][j + x_offset])
                    std::cout << 'X';
                else if(h1.map_[i][j] || h2.map_[i + y_offset][j + x_offset])
                    std::cout << '1';
                else
                    std::cout << '0';
            }

            std::cout << std::endl;
        }
    }

    for(int i = y1; i < y2; ++i) {
        for(int j = x1; j < x2; ++j) {
            // TODO: Check Attack and Shield map collisions
            if(h1.map_[i][j] && h2.map_[i+y_offset][j+x_offset])
                return DAMAGE;
        }
    }

    return NONE;
}
