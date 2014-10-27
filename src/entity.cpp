#include "entity.hpp"
#include "debug.hpp"

Entity::Entity(float width, float height) :
        super(0, 0, width, height),
        health_(20),
        type_(UNKNOWN)
{}

Entity::Entity(float x, float y, float width, float height) :
        super(x, y, width, height),
        health_(20),
        type_(UNKNOWN)
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

bool Entity::SortByYCoordinateAsc::operator()(Entity* e1, Entity* e2) const {
    return e1->y() < e2->y() or (e1->y() == e2->y() and e1->x() < e2->x());
}

float Entity::Distance(Entity* entity) const {
    return center().dist(entity->center());
}

EntityType Entity::type() const {
    return type_;
}
