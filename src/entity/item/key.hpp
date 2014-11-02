#pragma once

#include "../item.hpp"
#include "../../graphic/spritesheet.hpp"

class Key : public Item {
public:
    typedef Item super;
    enum Type {
        BOSS, SMALL
    };

    static SpriteSheet* SPRITESHEET;
    static std::vector<Sprite*> KEYS;
    static sf::SoundBuffer* GET_SOUND;

    static void Load();

    Key(Key::Type type, const std::string& name, float x, float y);

    bool HandleCollisionWith(Mob* mob);

private:
    std::string name_;
    Key::Type key_type_;
};
