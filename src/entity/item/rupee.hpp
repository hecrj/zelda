#pragma once

#include "../item.hpp"
#include "../../graphic/spritesheet.hpp"

class Rupee : public Item {
public:
    typedef Item super;
    enum Type {
        GREEN, BLUE, RED
    };

    static SpriteSheet* RUPEES_SPRITESHEET;
    static std::vector<Sprite*> RUPEES;

    static void Load();
    static Rupee* Random(float x, float y);

    Rupee(Rupee::Type type, float x, float y);

    bool HandleCollisionWith(Mob* mob);

private:
    Rupee::Type rupee_type_;
};
