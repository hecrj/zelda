#include "entity.hpp"
#include "debug.hpp"

Entity::Entity(const char *name, int width, int height) :
        super(0, 0, width, height),
        name_(name),
        alive_(true)
{}

Entity::Entity(const char *name, float x, float y, float width, float height) :
        super(x, y, width, height),
        name_(name),
        alive_(true)
{}

std::string Entity::name() const {
    return name_;
}

bool Entity::alive() const {
    return alive_;
}

void Entity::set_position(float x, float y) {
    position_.x = x;
    position_.y = y;
}

void Entity::set_position(const vec2f &position) {
    set_position(position.x, position.y);
}

void Entity::Receive(Entity from) {
    // TODO: Messages?
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
