#include "entity.hpp"
#include "debug.hpp"

Entity::Entity(float width, float height) :
        super(0, 0, width, height),
        health_(100)
{}

Entity::Entity(float x, float y, float width, float height) :
        super(x, y, width, height),
        health_(100)
{}

bool Entity::IsAlive() const {
    return health_ > 0;
}

void Entity::Kill() {
    health_ = 0;
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

bool Entity::IsEntity() const {
    return true;
}

int Entity::health() const {
    return health_;
}

void Entity::Damage(int damage) {
    health_ -= damage;
}
