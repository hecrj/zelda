#pragma once

#include "../object.hpp"

class Door : public Object {
public:
    typedef Object super;

    static sf::SoundBuffer* OPEN_SOUND;
    static void Load();

    Door();
};