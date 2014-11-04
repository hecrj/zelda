#include "pole_switch.hpp"
#include "pole.hpp"
#include "../../graphic/effect/timer.hpp"

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

void PoleSwitch::Damage(Entity* from, int amount) {
    if(Pole::IN_TRANSITION)
        return;

    Pole::OPEN = Pole::OPEN == Pole::BLUE ? Pole::YELLOW : Pole::BLUE;
    Pole::IN_TRANSITION = true;
    is_vulnerable_ = false;

    ChangeEffect(new Timer(0.2, [this]{
        is_vulnerable_ = true;
        Pole::IN_TRANSITION = false;
    }));
}

bool PoleSwitch::CanCollideWith(RectangleShape* rectangle) const {
    return not rectangle->IsEntity() or ((Entity*)rectangle)->type() == PLAYER;
}
