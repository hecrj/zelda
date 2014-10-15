#include "link.hpp"
#include "action/move.hpp"

SpriteSheet* Link::MOVE_SPRITE_SHEET;
std::vector<Animation*> Link::MOVE_ANIMATIONS;

void Link::Load() {
    MOVE_SPRITE_SHEET = new SpriteSheet("charset/link/move_shield.png", 147, 108, 21, 27);
    MOVE_ANIMATIONS = {
            new Animation(MOVE_SPRITE_SHEET->GetSprites(0, 7), 3, 60),
            new Animation(MOVE_SPRITE_SHEET->GetSprites(1, 7), 3, 60),
            new Animation(MOVE_SPRITE_SHEET->GetSprites(2, 7), 3, 60),
            new Animation(MOVE_SPRITE_SHEET->GetSprites(3, 7), 3, 60)
    };

    MOVE_ANIMATIONS[Dir::DOWN.index()]->set_ping_pong(true);
    MOVE_ANIMATIONS[Dir::UP.index()]->set_ping_pong(true);
}

Link::Link(Level* level) :
        super(
                "link",
                level,
                vec2f(4.0f, 12.0f),
                vec2f(16.0f, 24.0f),
                new ::Move(this, MOVE_ANIMATIONS)
        )
{}
