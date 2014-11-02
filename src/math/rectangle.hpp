#pragma once

#include "vec2.hpp"
#include "../graphic/collision.hpp"
#include "../graphic/drawable.hpp"

class Mob;
class Rectangle : public Drawable {
public:
    typedef Drawable super;
    Rectangle(float x, float y, float width, float height);

    float x();
    float y();
    vec2f position() const;
    vec2f top_center() const;
    vec2f center() const;
    vec2f bottom_right() const;
    vec2f bottom_right(const vec2f &pos) const;
    float width() const;
    float height() const;
    float Distance(const Rectangle* rectangle) const;

    virtual bool CanCollideWith(Rectangle* rectangle) const;
    virtual bool CollidesWith(Rectangle const * rectangle) const;
    virtual bool HandleCollisionWith(Mob* mob);
    virtual Collision CollisionType(Rectangle* rectangle) const;

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
