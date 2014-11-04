#include "plant.hpp"
#include "../item/rupee.hpp"
#include "../../audio/sound.hpp"

sf::SoundBuffer* Plant::CUT_SOUND;

void Plant::Load() {
    CUT_SOUND = Sound::Buffer("plant/cut.wav");
}

Plant::Plant(Sprite* sprite, float x, float y) :
        super(sprite, x, y)
{
    health_ = 1;
    type_ = PLANT;
    die_sound_ = CUT_SOUND;
}

bool Plant::CanReceiveDamageFrom(RectangleShape const* rectangle) const {
    return rectangle->IsEntity() and ((Entity*) rectangle)->type() == PLAYER;
}
