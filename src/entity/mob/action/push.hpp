#pragma once

#include "../action.hpp"
#include "../../../graphic/animation.hpp"
#include "move.hpp"

class Push : public Action {
public:
    typedef Action super;
    Push(Mob* mob, Action* move, const vec2f& direction, int intensity, float duration);

    bool IsTemporary() const;
    bool IsBlocking() const;
    bool IsFinished() const;

    void Update(double delta);

private:
    vec2f direction_;
    int intensity_;
    float duration_;
    float accum_;
};
