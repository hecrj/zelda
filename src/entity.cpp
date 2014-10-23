#include "entity.hpp"
#include "debug.hpp"

Entity::Entity(float width, float height) :
        super(0, 0, width, height),
        health_(100)
{}

Entity::Entity(float x, float y, float width, float height, int health) :
        super(x, y, width, height),
        health_(health)
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

void Entity::Damage(Entity* from, int damage) {
    health_ -= damage;
}

bool Entity::IsMob() const {
    return false;
}
