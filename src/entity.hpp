#pragma once

#include "math/vec2.hpp"
#include <string>

class Entity {
public:
    Entity(const char* name, int width, int height);
    Entity(const char* name, const vec2f& tleft, const vec2f& bright);

    std::string name() const;
    vec2f position() const;
    vec2f top_center() const;
    vec2f center() const;
    vec2f top_left() const;
    vec2f top_left(vec2f& pos) const;
    vec2f bottom_right() const;
    vec2f bottom_right(vec2f &pos) const;
    float width() const;
    float height() const;
    bool alive() const;
    bool Collides(const Entity& entity) const;

    void set_position(const vec2f& position);
    void set_position(float x, float y);
    void Receive(Entity from);
    void Kill();
    virtual void Update(float delta);
    virtual void Render() const;

private:
    std::string name_;
    vec2f top_left_;
    vec2f bottom_right_;
    vec2f position_;
    float width_;
    float height_;
    bool alive_;
};
