#include "link.hpp"
#include "action/move.hpp"
#include "action/attack.hpp"

SpriteSheet* Link::MOVE_SPRITE_SHEET;
std::vector<Animation*> Link::MOVE_ANIMATIONS;
SpriteSheet* Link::ATTACK_SPRITE_SHEET;
std::vector<Animation*> Link::ATTACK_ANIMATIONS;

void Link::Load() {
    MOVE_SPRITE_SHEET = new SpriteSheet("charset/link/move_shield.png", 147, 108, 21, 27);
    MOVE_ANIMATIONS = {
            new Animation(MOVE_SPRITE_SHEET->GetSprites(0, 7), 3, 60, vec2f(0.0f, -12.0f)),
            new Animation(MOVE_SPRITE_SHEET->GetSprites(1, 7), 3, 60, vec2f(0.0f, -12.0f)),
            new Animation(MOVE_SPRITE_SHEET->GetSprites(2, 7), 3, 60, vec2f(0.0f, -12.0f)),
            new Animation(MOVE_SPRITE_SHEET->GetSprites(3, 7), 3, 60, vec2f(0.0f, -12.0f))
    };

    MOVE_ANIMATIONS[Dir::DOWN.index()]->set_ping_pong(true);
    MOVE_ANIMATIONS[Dir::UP.index()]->set_ping_pong(true);

    ATTACK_SPRITE_SHEET = new SpriteSheet("charset/link/attack_sword.png", 324, 144, 36, 36);
    ATTACK_ANIMATIONS = {
            new Animation(ATTACK_SPRITE_SHEET->GetSprites(0, 6), 0, 31, vec2f(0.0f, -10.0f)),
            new Animation(ATTACK_SPRITE_SHEET->GetSprites(1, 9), 0, 20, vec2f(-11.0f, -23.0f)),
            new Animation(ATTACK_SPRITE_SHEET->GetSprites(2, 9), 0, 20, vec2f(-2.0f, -12.0f)),
            new Animation(ATTACK_SPRITE_SHEET->GetSprites(3, 9), 0, 20, vec2f(-11.0f, -12.0f))
    };
}

Link::Link(Level* level) :
        super(
                "link",
                level,
                0.0f, 0.0f, 19.0f, 14.0f,
                new ::Move(this, MOVE_ANIMATIONS)
        )
{
    RegisterAction("attack", new Attack(this, ATTACK_ANIMATIONS));
}
