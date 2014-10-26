#include "stalfos.hpp"

#include "action/move.hpp"

SpriteSheet* Stalfos::MOVE_SPRITE_SHEET;
std::vector<SpriteSet*> Stalfos::MOVE_ANIMATIONS;

void Stalfos::Load() {
    MOVE_SPRITE_SHEET = new SpriteSheet("charset/stalfos/move.png", 36, 144, 18, 36);
    MOVE_ANIMATIONS = {
            new SpriteSet(MOVE_SPRITE_SHEET->GetSprites(0, 2), 0, 100, vec2f(0.0f, -16.0f)),
            new SpriteSet(MOVE_SPRITE_SHEET->GetSprites(1, 2), 0, 100, vec2f(0.0f, -16.0f)),
            new SpriteSet(MOVE_SPRITE_SHEET->GetSprites(2, 2), 0, 200, vec2f(0.0f, -16.0f)),
            new SpriteSet(MOVE_SPRITE_SHEET->GetSprites(3, 2), 0, 150, vec2f(0.0f, -16.0f))
    };
}

Stalfos::Stalfos(Level* level) :
        super(
                level,
                0.0f, 0.0f, 20.0f, 14.0f,
                new ::Move(this, MOVE_ANIMATIONS)
        )
{

}
