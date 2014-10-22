#include "push.hpp"
#include "../../mob.hpp"

Push::Push(Mob* mob, Action* move, const vec2f& direction, int intensity, float duration) :
        super(mob, move->animations()),
        direction_(direction),
        intensity_(intensity),
        duration_(duration),
        accum_(0)
{}

bool Push::IsTemporary() const {
    return true;
}

bool Push::IsBlocking() const {
    return true;
}

bool Push::IsFinished() const {
    return accum_ >= duration_;
}

void Push::Update(double delta) {
    mob_->Slide(direction_, intensity_, delta);
    accum_ += delta;
}
