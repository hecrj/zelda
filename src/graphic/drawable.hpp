#pragma once

#include "effect.hpp"

class Drawable {
public:
    Drawable();
    ~Drawable();

    virtual bool IsHitbox() const;
    virtual bool IsEntity() const;

    void ChangeEffect(Effect* effect);
    void Tick(double delta);
    void Render() const;

    virtual void Update(double delta) = 0;
    virtual void Draw() const = 0;

protected:
    Effect* current_effect_;
};
