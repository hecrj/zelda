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
