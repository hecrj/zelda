#include "hud.hpp"

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
    glLoadIdentity();

    int health = player_->health();

    for(int i = 0; i < 5; ++i) {
        if(health >= 4) {
            HEARTS[4]->Render(vec2f(5 + 16 * i, 5));
            health -= 4;
        } else {
            HEARTS[health]->Render(vec2f(5 + 16 * i, 5));
            health = 0;
        }
    }
}
