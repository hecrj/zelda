#pragma once

#include "../object.hpp"

class Plant : public Object {
public:
    typedef Object super;

    static sf::SoundBuffer* CUT_SOUND;
    static void Load();

    Plant(Sprite* sprite, float x, float y);

    bool CanReceiveDamageFrom(RectangleShape const * rectangle) const;
};
