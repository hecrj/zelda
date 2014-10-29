#pragma once

#include "math/vec2.hpp"
#include "graphic/hitbox.hpp"
#include "entity/entity_type.hpp"
#include "graphic/effect.hpp"
#include <string>

class Level;
class Entity : public Hitbox {
public:
    typedef Hitbox super;
    Entity(float width, float height);
    Entity(float x, float y, float width, float height);
    ~Entity();

    int health() const;
    EntityType type() const;
    bool IsAlive() const;
    float Distance(Entity* entity) const;
    bool IsEntity() const;
    bool IsFinallyDead() const;
    virtual bool moving() const;
    virtual bool IsMob() const;

    void set_level(Level* level);
    void NotifyCollisions();

    void Kill();
    virtual void Die();
    virtual void Dead();
    virtual void Damage(Entity* from, int damage);

    struct SortByYCoordinateAsc {
        bool operator() (Entity* e1, Entity* e2) const;
    };

protected:
    Level* level_;
    int health_;
    EntityType type_;
    Effect* die_effect_;
};
