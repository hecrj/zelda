#pragma once

#include "math/vec2.hpp"
#include "graphic/hitbox.hpp"
#include "math/rectangle.hpp"
#include <string>

class Entity : public Hitbox {
public:
    typedef Hitbox super;
    Entity(float width, float height);
    Entity(float x, float y, float width, float height);

    bool alive() const;
    virtual bool moving() const;

    void Kill();
    virtual void Update(double delta);
    virtual void Render() const;

private:
    bool alive_;
};
