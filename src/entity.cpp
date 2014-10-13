#include "entity.hpp"

Entity::Entity(const char *name, int width, int height) : Entity(name, vec2f(0,0), vec2f(width-1, height-1))
{}

Entity::Entity(const char *name, const vec2f& tleft, const vec2f& bright) :
        name_(name),
        top_left_(tleft),
        bottom_right_(bright),
        position_(vec2f(0,0)),
        alive_(true),
        width_(bright.x - tleft.x),
        height_(bright.y - tleft.y)
{}

std::string Entity::name() const {
    return name_;
}

vec2f Entity::position() const {
    return position_;
}

vec2f Entity::top_center() const {
    vec2f v = vec2f(width_ / 2.0f, 0);
    return position_ + v;
}

vec2f Entity::center() const {
    vec2f v = vec2f(width_ / 2.0f, height_ / 2.0f);
    return position_ + v;
}

vec2f Entity::top_left() const {
    return top_left(position_);
}

vec2f Entity::top_left(const vec2f& pos) const {
    return top_left_ + pos;
}

vec2f Entity::bottom_right() const {
    return bottom_right(position_);
}

vec2f Entity::bottom_right(const vec2f &pos) const {
    return bottom_right_ + pos;
}

float Entity::width() const {
    return width_;
}

float Entity::height() const {
    return height_;
}

bool Entity::alive() const {
    return alive_;
}

bool Entity::Collides(const Entity &entity) const {
    return true;
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
    alive_ = true;
}

void Entity::Update(double delta) {
    // Do nothing
}

void Entity::Render() const {
    // Do nothing
}
