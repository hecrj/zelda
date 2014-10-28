#pragma once

#include "../effect.hpp"

class RotationFade : public Effect {
public:
    typedef Effect super;
    RotationFade(Entity* entity, float duration);
};