#include <iostream>
#include <GL/gl.h>
#include "rectangle.hpp"

Rectangle::Rectangle(float x, float y, float width, float height) :
        position_(vec2f(x, y)),
        width_(width),
        height_(height)
{}

vec2f Rectangle::position() const {
    return position_;
}

vec2f Rectangle::top_center() const {
    vec2f v = vec2f(width_ / 2.0f, 0);
    return position_ + v;
}

vec2f Rectangle::center() const {
    vec2f v = vec2f(width_ / 2.0f, height_ / 2.0f);
    return position_ + v;
}

vec2f Rectangle::bottom_right() const {
    return bottom_right(position_);
}

vec2f Rectangle::bottom_right(const vec2f &pos) const {
    return vec2f(width_, height_) + pos;
}

float Rectangle::width() const {
    return width_;
}

float Rectangle::height() const {
    return height_;
}

float Rectangle::x() {
    return position_.x;
}

float Rectangle::y() {
    return position_.y;
}

void Rectangle::set_position(float x, float y) {
    position_.x = x;
    position_.y = y;
}

void Rectangle::set_position(const vec2f &position) {
    set_position(position.x, position.y);
}


bool Rectangle::CanCollideWith(Rectangle* rectangle) const {
    return true;
}

bool Rectangle::CollidesWith(Rectangle* rectangle) const {
    const vec2f& rposition = rectangle->position();

    return !(
            position_.x + width_ < rposition.x ||
            rposition.x + rectangle->width_ < position_.x ||
            position_.y + height_ < rposition.y ||
            rposition.y + rectangle->height_ < position_.y
    );
}

void Rectangle::Print() const {
    std::cout << "(" << position_.x << ", " << position_.y << ") -> (" <<
            position_.x + width_ << ", " << position_.y + height_ << ")" << std::endl;
}

void Rectangle::Render(float r, float g, float b) const {
    glColor4f(r, g, b, 1);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_QUADS);

    glVertex2f(position_.x, position_.y);
    glVertex2f(position_.x + width_, position_.y);
    glVertex2f(position_.x + width_, position_.y + height_);
    glVertex2f(position_.x, position_.y + height_);

    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor4f(1, 1, 1, 1);
}

bool Rectangle::IsHitbox() const {
    return false;
}
