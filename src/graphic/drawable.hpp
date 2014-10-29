#include "effect.hpp"

#pragma once

class Drawable {
public:
    Drawable();
    ~Drawable();

    void ChangeEffect(Effect* effect);
    void Render() const;

    virtual void Update(double delta);
    virtual void Draw() const = 0;

protected:
    Effect* current_effect_;
};
