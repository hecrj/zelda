#include <iostream>
#include "animation.hpp"

Animation::Animation(const std::vector<Sprite*>& sprites, int idle_index, int interval, vec2f position) :
        sprites_(sprites),
        position_(position),
        idle_index_(idle_index),
        interval_(interval),
        current_frame_(idle_index),
        accum_(0),
        ping_pong_(false),
        ascending_(true),
        finished_(false),
        width_(0),
        height_(0)
{
    for(Sprite* sprite : sprites_) {
        if(sprite->width() > width_)
            width_ = sprite->width();

        if(sprite->height() > height_)
            height_ = sprite->height();
    }
}

Animation::Animation(const std::vector<Sprite*>& sprites, int idle_index, int interval) :
        Animation(sprites, idle_index, interval, vec2f(0, 0))
{}


int Animation::current_frame() const {
    return current_frame_;
}

void Animation::set_current_frame(int frame) {
    current_frame_ = frame;
}

void Animation::Reset() {
    current_frame_ = idle_index_;
    accum_ = 0;
    finished_ = false;
}

void Animation::Update(double delta) {
    accum_ += delta * 1000;

    if(accum_ > interval_) {
        if(ping_pong_) {
            current_frame_ = current_frame_ + (ascending_ ? 1 : -1);

            if(current_frame_ < 1 || current_frame_ >= (sprites_.size() - 1))
                ascending_ = !ascending_;
        } else {
            current_frame_ = (current_frame_ + 1);

            if(current_frame_ >= sprites_.size()) {
                finished_ = true;
                current_frame_ = 0;
            }
        }

        accum_ -= interval_;
    }
}

void Animation::Render(vec2f position) const {
    sprites_[current_frame_]->Render(position + position_);
}

void Animation::set_ping_pong(bool ping_pong) {
    ping_pong_ = ping_pong;
}

bool Animation::IsFinished() const {
    return finished_;
}

vec2f Animation::position() const {
    return position_;
}

float Animation::width() {
    return width_;
}

float Animation::height() {
    return height_;
}

Hitmap* Animation::CurrentHitmap() const {
    return sprites_[current_frame_]->hitmap();
}
