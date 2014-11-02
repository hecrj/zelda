#include "key.hpp"
#include "../mob.hpp"
#include "../mob/link.hpp"
#include "../../graphic/effect/bounce.hpp"
#include "../../audio/sound.hpp"

SpriteSheet* Key::SPRITESHEET;
std::vector<Sprite*> Key::KEYS;
sf::SoundBuffer* Key::GET_SOUND;

void Key::Load() {
    SPRITESHEET = new SpriteSheet("item/keys.png", 32, 16, 16, 16);
    KEYS = SPRITESHEET->GetSprites(0, 3);
    GET_SOUND = Sound::Buffer("rupee/get.wav");
}

Key::Key(Key::Type type, const std::string& name, float x, float y) :
        super(KEYS[type], x, y, vec2f(0, -10)),
        name_(name),
        key_type_(type)
{
    die_sound_ = GET_SOUND;
    ChangeEffect(new Bounce(12, 0.25));
}

bool Key::HandleCollisionWith(Mob* mob) {
    if(not IsAlive())
        return false;

    if(key_type_ == SMALL) {
        ((Link*)mob)->AddSmallKey(name_);
    } else {
        ((Link*)mob)->AddBossKey(name_);
    }

    Kill();
    return false;
}
