#pragma once

#include "../effect.hpp"
#include "../drawable.hpp"

class RotationFade : public Effect {
public:
    typedef Effect super;
    static const float REDUCTION;
    static const float ROTATION;
    RotationFade() ;

    bool IsFinished() const;

    void Tick(double delta);
    void Render() const;

private:
    float rotation_;
    float size_;
    float final_size_;
};
