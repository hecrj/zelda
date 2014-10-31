#include "link.hpp"
#include "action/move.hpp"
#include "action/attack.hpp"
#include "../../audio/sound.hpp"

SpriteSheet* Link::MOVE_SPRITE_SHEET;
std::vector<SpriteSet*> Link::MOVE_ANIMATIONS;
SpriteSheet* Link::ATTACK_SPRITE_SHEET;
std::vector<SpriteSet*> Link::ATTACK_ANIMATIONS;
sf::SoundBuffer* Link::ATTACK_SOUND;
sf::SoundBuffer* Link::HURT_SOUND;

void Link::Load() {
    MOVE_SPRITE_SHEET = new SpriteSheet("charset/link/move_shield.png", 147, 108, 21, 27);
    MOVE_ANIMATIONS = {
            new SpriteSet(MOVE_SPRITE_SHEET->GetSprites(0, 7), 3, vec2f(0.0f, -12.0f), {30, 40, 50, 40, 50, 40, 30}),
            new SpriteSet(MOVE_SPRITE_SHEET->GetSprites(1, 7), 3, vec2f(0.0f, -12.0f), {30, 40, 50, 40, 50, 40, 30}),
            new SpriteSet(MOVE_SPRITE_SHEET->GetSprites(2, 7), 3, vec2f(0.0f, -12.0f), {30, 40, 40, 40, 40, 30, 30}),
            new SpriteSet(MOVE_SPRITE_SHEET->GetSprites(3, 7), 3, vec2f(0.0f, -12.0f), {30, 30, 40, 40, 40, 40, 30})
    };

    MOVE_ANIMATIONS[Dir::DOWN.index()]->ping_pong = true;
    MOVE_ANIMATIONS[Dir::UP.index()]->ping_pong = true;

    ATTACK_SPRITE_SHEET = new SpriteSheet("charset/link/attack_sword.png", 324, 144, 36, 36);
    ATTACK_SPRITE_SHEET->set_hit_spritesheet("charset/link/attack_sword_hit.png");

    ATTACK_ANIMATIONS = {
            new SpriteSet(ATTACK_SPRITE_SHEET->GetSprites(0, 6), 0, 31, vec2f(-2.0f, -10.0f)),
            new SpriteSet(ATTACK_SPRITE_SHEET->GetSprites(1, 9), 0, 20, vec2f(-11.0f, -23.0f)),
            new SpriteSet(ATTACK_SPRITE_SHEET->GetSprites(2, 9), 0, 20, vec2f(-2.0f, -12.0f)),
            new SpriteSet(ATTACK_SPRITE_SHEET->GetSprites(3, 9), 0, 20, vec2f(-11.0f, -12.0f))
    };

    ATTACK_SOUND = Sound::Buffer("link/sword1.wav");
    HURT_SOUND = Sound::Buffer("link/hurt.wav");
}

Link::Link() :
        super(
                0.0f, 0.0f, 20.0f, 14.0f,
                new ::Move(this, MOVE_ANIMATIONS)
        ),
        rupees_(0)
{
    type_ = PLAYER;
    attack_sound_ = ATTACK_SOUND;
    hurt_sound_ = HURT_SOUND;

    AddAction("attack", new Attack(this, ATTACK_ANIMATIONS));
}

void Link::UpdateRupees(int rupees) {
    rupees_ += rupees;

    if(rupees_ > 99)
        rupees_ = 99;
}

int Link::rupees() const {
    return rupees_;
}
