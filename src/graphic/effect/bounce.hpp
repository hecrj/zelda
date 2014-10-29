#pragma once

#include "../effect.hpp"
#include "../../math/vec2.hpp"
#include "../../math/rectangle.hpp"

class Bounce : public Effect {
public:
    typedef Effect super;
    static const float GRAVITY;

    Bounce(Drawable* drawable, float height, float duration);

    bool IsFinished() const;

    void Tick(double delta);
    void Render() const;
    void Leave();

private:
    vec2f position_;
    float speed_;
    float final_speed_;
};
