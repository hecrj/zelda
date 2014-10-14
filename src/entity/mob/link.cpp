#include "link.hpp"
#include "action/move.hpp"

SpriteSheet* const Link::MOVE_SPRITE_SHEET = new SpriteSheet("charset/link_move", 21, 27);
const std::vector<Animation*> Link::MOVE_ANIMATIONS = {
        new Animation(MOVE_SPRITE_SHEET->GetSprites(0, 7), 50),
        new Animation(MOVE_SPRITE_SHEET->GetSprites(1, 7), 50),
        new Animation(MOVE_SPRITE_SHEET->GetSprites(2, 7), 50),
        new Animation(MOVE_SPRITE_SHEET->GetSprites(3, 7), 50)
};

Link::Link(Level* level) :
        super(
                "link",
                level,
                vec2f(4.0f, 12.0f),
                vec2f(16.0f, 24.0f),
                new ::Move(this, MOVE_ANIMATIONS)
        )
{}
