#ifdef _WIN32
#include <Windows.h>
#endif
#include "hud.hpp"
#include "entity/item/rupee.hpp"
#include "game.hpp"
#include "graphic/font.hpp"
#include "entity/item/key.hpp"

SpriteSheet* Hud::HEARTS_SPRITESHEET;
std::vector<Sprite*> Hud::HEARTS;

void Hud::Load() {
    HEARTS_SPRITESHEET = new SpriteSheet("hud/hearts.png", 80, 18, 16, 18);
    HEARTS = HEARTS_SPRITESHEET->GetSprites(0, 5);
}

Hud::Hud(Link *player) :
        player_(player)
{}


void Hud::Render() const {
    glPushMatrix();
    glLoadIdentity();
    glScalef(Game::SCALE, Game::SCALE, 0);

    int health = player_->health();

    for(int i = 0; i < 5; ++i) {
        if(health >= 4) {
            HEARTS[4]->Render(vec2f(5 + 16 * i, 5));
            health -= 4;
        } else {
            if (health >= 0) {
                HEARTS[health]->Render(vec2f(5 + 16 * i, 5));
            }

            health = 0;
        }
    }

    vec2f position(vec2f(5, 10 + HEARTS[0]->height()));
    Rupee::RUPEES[Rupee::GREEN]->Render(position);

    Key::KEYS[Key::SMALL]->Render(position + vec2f(-4, Rupee::RUPEES[Rupee::Type::GREEN]->height() + 5));

    if(player_->boss_keys() > 0)
        Key::KEYS[Key::BOSS]->Render(position + vec2f(-4, Rupee::RUPEES[Rupee::Type::GREEN]->height() + 25));

    glScalef(0.5, 0.5, 0);
    char buffer[4];
    sprintf(buffer, "%02d", player_->rupees());
    Font::Render(position.x + Rupee::RUPEES[Rupee::Type::GREEN]->width() + 20, position.y + 32, buffer);

    sprintf(buffer, "%02d", player_->small_keys());
    Font::Render(position.x + Rupee::RUPEES[Rupee::Type::GREEN]->width() + 20, position.y + 75, buffer);
    glPopMatrix();
}
