#pragma once

#include "../effect.hpp"

class Float : public Effect {
public:
    typedef Effect super;
    Float(Drawable* drawable, int height, float duration);

    bool IsFinished() const;

    void Tick(double delta);
    void Render() const;

private:
    float speed_;
    float time_;
    float duration_;
};