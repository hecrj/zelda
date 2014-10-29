#pragma once

#include "../effect.hpp"
#include "../../math/vec2.hpp"
#include "../drawable.hpp"

class Bounce : public Effect {
public:
    typedef Effect super;
    static const float GRAVITY;

    Bounce(Drawable* drawable, float height, float duration);

    bool IsFinished() const;

    void Update(double delta);
    void Render() const;

private:
    vec2f position_;
    float speed_;
    float final_speed_;
};
