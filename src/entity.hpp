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

    int health() const;
    bool IsAlive() const;
    virtual bool moving() const;
    bool IsEntity() const;

    void Kill();
    virtual void Damage(Entity* from, int damage);
    virtual void Update(double delta);
    virtual void Render() const;

private:
    int health_;
};
