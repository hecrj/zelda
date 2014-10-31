#pragma once

#include "../effect.hpp"
#include "../drawable.hpp"

class RotationFade : public Effect {
public:
    typedef Effect super;
    RotationFade(float duration);
};
