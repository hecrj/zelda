#pragma once

#include "../object.hpp"

class PoleSwitch : public Entity {
public:
    typedef Entity super;

    PoleSwitch(float x, float y, Sprite* red, Sprite* yellow);

    Sprite* CurrentSprite() const;
    Sprite* CurrentSprite(vec2f& position) const;
    bool CanCollideWith(Rectangle* rectangle) const;

    void Draw() const;
    void Damage(Entity* from, int amount);

private:
    std::vector<Sprite*> sprites_;
};
