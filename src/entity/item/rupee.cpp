#include "rupee.hpp"
#include "../mob.hpp"
#include "../mob/link.hpp"
#include "../../graphic/effect/bounce.hpp"
#include "../../audio/sound.hpp"

SpriteSheet* Rupee::RUPEES_SPRITESHEET;
std::vector<Sprite*> Rupee::RUPEES;
sf::SoundBuffer* Rupee::GET_SOUND;

void Rupee::Load() {
    RUPEES_SPRITESHEET = new SpriteSheet("item/rupees.png", 27, 16, 9, 16);
    RUPEES = RUPEES_SPRITESHEET->GetSprites(0, 3);
    GET_SOUND = Sound::Buffer("rupee/get.wav");
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

    return new Rupee(type, x - RUPEES[type]->width() / 2.0f, y - (RUPEES[type]->height() - 10) / 2.0f);
}

Rupee::Rupee(Rupee::Type type, float x, float y) :
        super(RUPEES[type], x, y, vec2f(0, -10)),
        rupee_type_(type)
{
    die_sound_ = GET_SOUND;
    ChangeEffect(new Bounce(12, 0.25));
}

bool Rupee::HandleCollisionWith(Mob* mob) {
    if(not IsAlive())
        return false;

    int amount = rupee_type_ == Rupee::Type::GREEN ? 1 : rupee_type_ == Rupee::Type::BLUE ? 2 : 5;

    // Mob has to be a player
    ((Link*) mob)->UpdateRupees(amount);

    Kill();
    return false;
}
