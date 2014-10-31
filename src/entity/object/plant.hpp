#pragma once

#include "../object.hpp"

class Plant : public Object {
public:
    static sf::SoundBuffer* CUT_SOUND;

    static void Load();

    typedef Object super;
    Plant(Sprite* sprite, float x, float y);

    void Dead();
};