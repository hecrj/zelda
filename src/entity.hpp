#pragma once

#include "math/vec2.hpp"
#include "math/rectangle.hpp"
#include <string>

class Entity : public Rectangle {
public:
    typedef Rectangle super;
    Entity(const char* name, int width, int height);
    Entity(const char* name, float x, float y, float width, float height);

    std::string name() const;
    bool alive() const;
    bool Collides(const Entity& entity) const;

    void set_position(const vec2f& position);
    void set_position(float x, float y);
    void Receive(Entity from);
    void Kill();
    virtual void Update(double delta);
    virtual void Render() const;

private:
    std::string name_;
    bool alive_;
};
