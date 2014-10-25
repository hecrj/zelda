#pragma once

#include "math/vec2.hpp"
#include "graphic/hitbox.hpp"
#include <string>

class Entity : public Hitbox {
public:
    typedef Hitbox super;
    Entity(float width, float height);
    Entity(float x, float y, float width, float height, int health);

    int health() const;
    bool IsAlive() const;
    virtual bool moving() const;
    bool IsEntity() const;
    virtual bool IsMob() const;

    void Kill();
    virtual void Damage(Entity* from, int damage);
    virtual void Update(double delta);
    virtual void Render() const;

    struct SortByYCoordinateAsc {
        bool operator() (Entity* e1, Entity* e2) const;
    };

private:
    int health_;
};
