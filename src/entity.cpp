#include "entity.hpp"
#include "debug.hpp"

Entity::Entity(float width, float height) :
        super(0, 0, width, height),
        alive_(true)
{}

Entity::Entity(float x, float y, float width, float height) :
        super(x, y, width, height),
        alive_(true)
{}

bool Entity::alive() const {
    return alive_;
}

void Entity::Kill() {
    alive_ = false;
}

void Entity::Update(double delta) {
    // Do nothing
}

void Entity::Render() const {
    if(Debug::enabled)
        super::Render(1, 0, 0);
}

bool Entity::moving() const {
    return false;
}
