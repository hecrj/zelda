#ifdef _WIN32
#include <Windows.h>
#endif
#include <sstream>
#include "font.hpp"
#include "../game.hpp"

const int Font::WIDTH = 10;
const int Font::HEIGHT = 27;
SpriteSheet* Font::FONT;
std::vector<Sprite*> Font::UPPERCASE;
std::vector<Sprite*> Font::LOWERCASE;
std::vector<Sprite*> Font::DIGITS;
std::vector<Sprite*> Font::SPECIAL;

void Font::Load() {
    FONT = new SpriteSheet("font.png", 260, 108, WIDTH, HEIGHT);
    UPPERCASE = FONT->GetSprites(0, 26);
    LOWERCASE = FONT->GetSprites(1, 26);
    DIGITS = FONT->GetSprites(2, 10);
    SPECIAL = FONT->GetSprites(3, 3);
}

void Font::Render(float x, float y, const char* text) {
    int i = 0;
    char c;
    vec2f pos(x, y);

    glBindTexture(GL_TEXTURE_2D, FONT->texture());
    glBegin(GL_QUADS);

    while(text[i] != '\0') {
        c = text[i];

        if('A' <= c && c <= 'Z') {
            UPPERCASE[c - 'A']->DrawGeom(pos);
        } else if('a' <= c && c <= 'z') {
            LOWERCASE[c - 'a']->DrawGeom(pos);
        } else if('0' <= c && c <= '9') {
            DIGITS[c - '0']->DrawGeom(pos);
        } else if(',' <= c && c <= '.') {
            SPECIAL[c - ',']->DrawGeom(pos);
        } else if(c != ' ') {
            std::stringstream ss;
            ss << c;
            Game::Error("Impossible to render font character:", ss.str());
        }

        pos.x += 10;
        ++i;
    }

    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
}
