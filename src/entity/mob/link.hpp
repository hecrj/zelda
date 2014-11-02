#pragma once

#include "../mob.hpp"
#include "../../graphic/spritesheet.hpp"

class Link : public Mob {
public:
    typedef Mob super;

    static SpriteSheet* MOVE_SPRITE_SHEET;
    static SpriteSheet* ATTACK_SPRITE_SHEET;

    static std::vector<SpriteSet*> MOVE_ANIMATIONS;
    static std::vector<SpriteSet*> ATTACK_ANIMATIONS;

    static sf::SoundBuffer* ATTACK_SOUND;
    static sf::SoundBuffer* HURT_SOUND;

    static void Load();

    Link();

    int rupees() const;

    void UpdateRupees(int rupees);

    bool CollidesWith(Rectangle const * rectangle) const;

private:
    int rupees_;
};
