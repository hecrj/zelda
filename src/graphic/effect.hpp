#pragma once

class Drawable;
class Effect {
public:
    Effect(Drawable* drawable);

    virtual bool IsFinished() const = 0;

    virtual void Update(double delta) = 0;
    virtual void Render() const = 0;

protected:
    Drawable* drawable_;
};
