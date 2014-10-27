#include "entity/mob/link.hpp"

#pragma once

class Hud {
public:
    static SpriteSheet* HEARTS_SPRITESHEET;
    static std::vector<Sprite*> HEARTS;

    static void Load();

    Hud(Link* player);

    void Render() const;

private:
    Link* player_;
};
