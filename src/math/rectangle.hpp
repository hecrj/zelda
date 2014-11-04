#pragma once

#include "vec2.hpp"
#include "../graphic/collision.hpp"
#include "../graphic/drawable.hpp"

class Mob;
class RectangleShape : public Drawable {
public:
    typedef Drawable super;
    RectangleShape(float x, float y, float width, float height);

    float x();
    float y();
    vec2f position() const;
    vec2f top_center() const;
    vec2f center() const;
    vec2f bottom_right() const;
    vec2f bottom_right(const vec2f &pos) const;
    float width() const;
    float height() const;
    float Distance(const RectangleShape* rectangle) const;

    virtual bool CanCollideWith(RectangleShape* rectangle) const;
    virtual bool CollidesWith(RectangleShape const * rectangle) const;
    virtual bool CanReceiveDamageFrom(RectangleShape const * rectangle) const;
    virtual bool HandleCollisionWith(Mob* mob);
    virtual Collision CollisionType(RectangleShape* rectangle) const;

    void set_position(const vec2f& position);
    void set_position(float x, float y);
    void DrawBox(float r, float g, float b) const;
    void Update(double delta);
    void Draw() const;
    void Print() const;

protected:
    vec2f position_;
    float width_;
    float height_;
};
