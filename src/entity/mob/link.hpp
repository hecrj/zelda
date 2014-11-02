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
    int small_keys() const;
    int boss_keys() const;

    void UpdateRupees(int rupees);
    void UpdateSmallKeys(int keys);
    void UpdateBossKeys(int keys);

    bool CollidesWith(Rectangle const * rectangle) const;
    bool HandleCollisionWith(Mob* mob);

private:
    int rupees_;
    int small_keys_;
    int boss_keys_;
};
