#include "../math/vec2.hpp"

#pragma once

class Animation {
public:
    Animation(vec2f entity_position, int sprite_interval);

    int current_frame() const;

    // TODO: void AddSprite(... sprite);
    void set_current_frame(int frame);
    void Update(double delta);

private:
    // TODO: Sprite vector
    vec2f dim_;
    vec2f entity_position_;
    int sprite_interval_;
    int current_frame_;
};
