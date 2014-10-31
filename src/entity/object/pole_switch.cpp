#include "pole_switch.hpp"
#include "pole.hpp"

PoleSwitch::PoleSwitch(float x, float y, Sprite* red, Sprite* yellow) :
        super(x, y, 16, 16),
        sprites_({red, yellow})
{}

Sprite* PoleSwitch::CurrentSprite() const {
    return sprites_[Pole::OPEN];
}


Sprite* PoleSwitch::CurrentSprite(vec2f& position) const {
    position.x = 0;
    position.y = 0;

    return sprites_[Pole::OPEN];
}

void PoleSwitch::Draw() const {
    sprites_[Pole::OPEN]->Render(position_);
}

bool PoleSwitch::IsVulnerable() const {
    return true;
}
