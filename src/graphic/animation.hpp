#pragma once

#include "sprite_set.hpp"

class Animation {
public:
    Animation(SpriteSet* spriteset);
    int current_frame() const;
    bool IsFinished() const;
    vec2f position() const;
    float width();
    float height();
    Pixelmap* HitMap() const;
    Pixelmap* DamageMap() const;

    void set_current_frame(int frame);
    void Reset();
    void Update(double delta);
    void Render(vec2f position) const;

private:
    SpriteSet* spriteset_;
    int current_frame_;
    int accum_;
    bool ascending_;
    bool finished_;
};
