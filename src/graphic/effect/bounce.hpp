#pragma once

#include "../effect.hpp"
#include "../../math/vec2.hpp"

class Bounce : public Effect {
public:
    static const float GRAVITY;

    Bounce(float height, float duration);

    bool IsFinished() const;

    void Update(double delta);
    void Render() const;

private:
    vec2f position_;
    float speed_;
    float final_speed_;
};