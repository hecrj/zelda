#include "spritesheet.hpp"

#pragma once

class Font {
public:
    static const int WIDTH;
    static const int HEIGHT;
    static SpriteSheet* FONT;
    static std::vector<Sprite*> UPPERCASE;
    static std::vector<Sprite*> LOWERCASE;
    static std::vector<Sprite*> DIGITS;

    static void Load();
    static void Render(float x, float y, const char* c);
};
