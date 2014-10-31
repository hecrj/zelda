#include "pole.hpp"

Pole::Type Pole::OPEN = BLUE;
Pole::Status Pole::INTERNAL_STATUS = BLUE_OPEN;

Pole::Pole(float x, float y, Type type, Sprite* closed, Sprite* transition) :
        super(x, y, 16, 16),
        type_(type),
        closed_(closed),
        transition_(transition)
{}

void Pole::Draw() const {
    if(INTERNAL_STATUS != TRANSITION) {
        if(type_ != OPEN)
            closed_->Render(position_);
    } else {
        transition_->Render(position_);
    }
}

bool Pole::CanCollideWith(Rectangle* rectangle) const {
    return not rectangle->IsEntity() or
            ((Entity*)rectangle)->type() != PLAYER or
                    INTERNAL_STATUS == TRANSITION or
                            type_ != OPEN;
}
