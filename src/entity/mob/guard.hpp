#pragma once

#include "../mob.hpp"
#include "../../graphic/spritesheet.hpp"

class Guard : public Mob {
public:
    typedef Mob super;

    static SpriteSheet* MOVE_SPRITE_SHEET;
    static std::vector<SpriteSet*> MOVE_ANIMATIONS;

    static void Load();

    Guard(Level* level);

    void Update(double delta);
};
