#pragma once

#include "../object.hpp"

class PoleSwitch : public Entity {
public:
    typedef Entity super;

    PoleSwitch(float x, float y, Sprite* red, Sprite* yellow);

    bool IsVulnerable() const;
    Sprite* CurrentSprite() const;
    Sprite* CurrentSprite(vec2f& position) const;

    void Draw() const;

private:
    std::vector<Sprite*> sprites_;
};
