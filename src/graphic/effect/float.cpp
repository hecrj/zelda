#include <GL/gl.h>
#include "float.hpp"
#include "../drawable.hpp"

Float::Float(int height, float duration) :
        duration_(duration),
        speed_(-height / duration),
        time_(0)
{}

bool Float::IsFinished() const {
    return time_ >= duration_;
}

void Float::Tick(double delta) {
    time_ += delta;
}

void Float::Render() const {
    glPushMatrix();
    glTranslatef(0, speed_ * time_, 0);
    drawable_->Draw();
    glPopMatrix();
}
