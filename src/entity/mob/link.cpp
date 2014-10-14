#include "link.hpp"
#include "action/move.hpp"
#include "../../graphic/spritesheet.hpp"

SpriteSheet* const MOVE_SPRITE_SHEET = new SpriteSheet("charset/link_move", 21, 27);
const std::vector<Animation*> Link::MOVE_ANIMATIONS = {
        // TODO: Populate Link move animations
        MOVE_SPRITE_SHEET->GetAnimation(0, 7, 50)
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
