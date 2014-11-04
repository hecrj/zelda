#include "event.hpp"

Event::Event(Level* level, float x, float y, float width, float height) :
        super(x, y, width, height),
        level_(level)
{}

bool Event::CanCollideWith(RectangleShape* rectangle) const {
    return rectangle->IsEntity() and ((Entity*)rectangle)->type() == PLAYER;
}
