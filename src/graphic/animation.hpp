#include "../math/vec2.hpp"
#include "sprite.hpp"
#include <vector>

#pragma once

class Animation {
public:
    Animation(const std::vector<Sprite*>& sprites, int idle_index, int interval);
    Animation(const std::vector<Sprite*>& sprites, int idle_index, int interval, vec2f position);

    int current_frame() const;

    void set_current_frame(int frame);
    void set_ping_pong(bool ping_pong);
    void Reset();
    void Update(double delta);
    void Render(vec2f position) const;

private:
    std::vector<Sprite*> sprites_;
    vec2f dim_;
    vec2f position_;
    int idle_index_;
    int interval_;
    int current_frame_;
    int accum;
    bool ping_pong_;
    bool ascending_;
};
