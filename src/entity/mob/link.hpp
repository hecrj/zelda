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
    bool has_key(const std::string& name) const;

    void UpdateRupees(int rupees);

    void AddSmallKey(const std::string& name);
    void AddBossKey(const std::string& name);

    void UpdateSmallKeys(int keys);
    void UpdateBossKeys(int keys);

    void Damage(Entity* from, int amount);

    bool CollidesWith(Rectangle const * rectangle) const;
    bool HandleCollisionWith(Mob* mob);

private:
    std::map<std::string, bool> keys_;
    int rupees_;
    int small_keys_;
    int boss_keys_;
};
