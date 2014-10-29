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

    if(xdir == 1)
        x = width_ + 5;
    else if(xdir == -1)
        x = -entity->width() - 5;

    if(ydir == 1)
        y = height_ + 5;
    else
        y = -entity->height() - 5;

    entity->set_position(position_ + vec2f(x, y));

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
