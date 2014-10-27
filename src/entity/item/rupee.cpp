#include "rupee.hpp"
#include "../mob.hpp"

SpriteSheet* Rupee::RUPEES_SPRITESHEET;
std::vector<Sprite*> Rupee::RUPEES;

void Rupee::Load() {
    RUPEES_SPRITESHEET = new SpriteSheet("item/rupees.png", 27, 16, 9, 16);
    RUPEES = RUPEES_SPRITESHEET->GetSprites(0, 3);
}

Rupee* Rupee::Random(float x, float y) {
    int r = rand() % 100;

    Rupee::Type type;

    if(r < 85)
        type = Rupee::Type::GREEN;
    else if(r < 97)
        type = Rupee::Type::BLUE;
    else
        type = Rupee::Type::RED;

    return new Rupee(type, x - 4.5f, y - 8.0f);
}

Rupee::Rupee(Rupee::Type type, float x, float y) :
        super(RUPEES[type], x, y),
        type_(type)
{}

bool Rupee::HandleCollisionWith(Mob* mob) {
    // TODO: Update Link rupees

    Kill();
    return false;
}
