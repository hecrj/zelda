#include <iostream>
#include "location.hpp"
#include "../entity/mob.hpp"
#include "../game.hpp"

Location::Location(float x, float y, float width, float height, const std::string& name, const std::string& orientation) :
        super(x, y, width, height),
        name_(name)
{
    if(orientation.empty())
        Game::Error("Orientation property not found at location: ", name_);

    set_orientation(orientation);
}

void Location::Place(Entity* entity) const {
    float x = 0;
    float y = 0;

    if(xdir == 1) {
        x = width_ / 2.0f + 5;
    } else if(xdir == -1) {
        x = -entity->width() - width_ / 2.0f - 5;
    }

    if(ydir == 1) {
        y = height_ / 2.0f + 5;
    } else {
        y = -entity->height() - height_ / 2.0f - 5;
    }

    if(xdir == 1 || xdir == -1)
        y = -entity->height() / 2.0f;

    if(ydir == 1 || ydir == -1)
        x = -entity->width() / 2.0f;

    entity->set_position(center() + vec2f(x, y));

    if(entity->IsMob()) {
        ((Mob*) entity)->set_facing(Dir::fromVector(vec2f(xdir, ydir)));
    }
}

void Location::set_orientation(const std::string& orientation) {
    xdir = ydir = 0;

    if(orientation == "DOWN") {
        ydir = 1;
    } else if(orientation == "UP") {
        ydir = -1;
    } else if(orientation == "RIGHT") {
        xdir = 1;
    } else if(orientation == "LEFT") {
        xdir = -1;
    }
}

const std::string& Location::name() const {
    return name_;
}
