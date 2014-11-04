#include <iostream>
#include <GL/gl.h>
#include "rectangle.hpp"
#include "../entity/mob.hpp"

RectangleShape::RectangleShape(float x, float y, float width, float height) :
        position_(vec2f(x, y)),
        width_(width),
        height_(height)
{}

vec2f RectangleShape::position() const {
    return position_;
}

vec2f RectangleShape::top_center() const {
    vec2f v = vec2f(width_ / 2.0f, 0);
    return position_ + v;
}

vec2f RectangleShape::center() const {
    vec2f v = vec2f(width_ / 2.0f, height_ / 2.0f);
    return position_ + v;
}

vec2f RectangleShape::bottom_right() const {
    return bottom_right(position_);
}

vec2f RectangleShape::bottom_right(const vec2f &pos) const {
    return vec2f(width_, height_) + pos;
}

float RectangleShape::width() const {
    return width_;
}

float RectangleShape::height() const {
    return height_;
}

float RectangleShape::x() {
    return position_.x;
}

float RectangleShape::y() {
    return position_.y;
}

void RectangleShape::set_position(float x, float y) {
    position_.x = x;
    position_.y = y;
}

void RectangleShape::set_position(const vec2f &position) {
    set_position(position.x, position.y);
}

bool RectangleShape::CanCollideWith(RectangleShape* rectangle) const {
    return rectangle != this;
}

bool RectangleShape::CollidesWith(RectangleShape const * rectangle) const {
    const vec2f& rposition = rectangle->position();

    return !(
            position_.x + width_ < rposition.x ||
            rposition.x + rectangle->width_ < position_.x ||
            position_.y + height_ < rposition.y ||
            rposition.y + rectangle->height_ < position_.y
    );
}

void RectangleShape::Print() const {
    std::cout << "(" << position_.x << ", " << position_.y << ") -> (" <<
            position_.x + width_ << ", " << position_.y + height_ << ")" << std::endl;
}

void RectangleShape::DrawBox(float r, float g, float b) const {
    glColor4f(r, g, b, 1);

    RectangleShape::Draw();

    glColor4f(1, 1, 1, 1);
}

Collision RectangleShape::CollisionType(RectangleShape* rectangle) const {
    return Collision::BLOCK;
}

bool RectangleShape::HandleCollisionWith(Mob* mob) {
    return true;
}

void RectangleShape::Draw() const {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_QUADS);

    glVertex2f(position_.x, position_.y);
    glVertex2f(position_.x + width_, position_.y);
    glVertex2f(position_.x + width_, position_.y + height_);
    glVertex2f(position_.x, position_.y + height_);

    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void RectangleShape::Update(double delta) {
    // Do nothing
}

float RectangleShape::Distance(const RectangleShape* rectangle) const {
    return center().dist(rectangle->center());
}

bool RectangleShape::CanReceiveDamageFrom(RectangleShape const* rectangle) const {
    return true;
}
