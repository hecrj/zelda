#pragma once

#include "../mob.hpp"
#include "../../graphic/spritesheet.hpp"

class Stalfos : public Mob {
public:
    typedef Mob super;

    static SpriteSheet* MOVE_SPRITE_SHEET;
    static std::vector<SpriteSet*> MOVE_ANIMATIONS;

    static void Load();

    Stalfos(const std::string& name, float x, float y, bool small_key, bool boss_key);

    void Dead();

private:
    std::string name_;
    bool small_key_;
    bool boss_key_;
};
