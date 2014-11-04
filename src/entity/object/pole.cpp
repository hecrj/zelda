#include "pole.hpp"

Pole::Type Pole::OPEN = BLUE;
bool Pole::IN_TRANSITION = false;

Pole::Pole(float x, float y, Type type, Sprite* closed, Sprite* transition) :
        super(x, y, 16, 16),
        type_(type),
        closed_(closed),
        transition_(transition)
{
    is_vulnerable_ = false;
}

void Pole::Draw() const {
    if(not IN_TRANSITION) {
        if(type_ != OPEN)
            closed_->Render(position_);
    } else {
        transition_->Render(position_);
    }
}

bool Pole::CanCollideWith(RectangleShape* rectangle) const {
    return IN_TRANSITION or type_ != OPEN;
}
