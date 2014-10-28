#include "hud.hpp"
#include "entity/item/rupee.hpp"
#include <GL/freeglut.h>

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

    vec2f position(vec2f(5, 10 + HEARTS[0]->height()));
    Rupee::RUPEES[Rupee::Type::GREEN]->Render(position);

    glRasterPos2i((int)(position.x + Rupee::RUPEES[Rupee::Type::GREEN]->width() + 3), (int)position.y + 15);
    char buffer[4];
    sprintf(buffer, "x%02d", player_->rupees());
    glutBitmapString(GLUT_BITMAP_9_BY_15, (unsigned char*)buffer);
}
