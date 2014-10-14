#include "../math/vec2.hpp"
#include "sprite.hpp"
#include <vector>

#pragma once

class Animation {
public:
    Animation(const std::vector<Sprite*>& sprites, int sprite_interval);
    Animation(const std::vector<Sprite*>& sprites, int sprite_interval, vec2f position);

    int current_frame() const;

    // TODO: void AddSprite(... sprite);
    void set_current_frame(int frame);
    void Update(double delta);

private:
    std::vector<Sprite*> sprites_;
    vec2f dim_;
    vec2f position_;
    int sprite_interval_;
    int current_frame_;
};
