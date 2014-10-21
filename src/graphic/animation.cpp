#include "animation.hpp"

Animation::Animation(SpriteSet* spriteset) :
        spriteset_(spriteset),
        current_frame_(spriteset->idle_index),
        accum_(0),
        ascending_(true),
        finished_(false)
{

}

int Animation::current_frame() const {
    return current_frame_;
}

void Animation::set_current_frame(int frame) {
    current_frame_ = frame;
}

void Animation::Reset() {
    current_frame_ = spriteset_->idle_index;
    accum_ = 0;
    finished_ = false;
}

void Animation::Update(double delta) {
    accum_ += delta * 1000;

    if(accum_ > spriteset_->interval) {
        if(spriteset_->ping_pong) {
            current_frame_ = current_frame_ + (ascending_ ? 1 : -1);

            if(current_frame_ < 1 || current_frame_ >= (spriteset_->sprites.size() - 1))
                ascending_ = !ascending_;
        } else {
            current_frame_ = (current_frame_ + 1);

            if(current_frame_ >= spriteset_->sprites.size()) {
                finished_ = true;
                current_frame_ = 0;
            }
        }

        accum_ -= spriteset_->interval;
    }
}

void Animation::Render(vec2f position) const {
    spriteset_->sprites[current_frame_]->Render(position + spriteset_->position);
}


bool Animation::IsFinished() const {
    return finished_;
}

vec2f Animation::position() const {
    return spriteset_->position;
}

float Animation::width() {
    return spriteset_->width;
}

float Animation::height() {
    return spriteset_->height;
}

Hitmap* Animation::CurrentHitmap() const {
    return spriteset_->sprites[current_frame_]->hitmap();
}
