#include "guard.hpp"

#include "action/move.hpp"
#include "../../graphic/hitbox/animation_hitbox.hpp"

SpriteSheet* Guard::MOVE_SPRITE_SHEET;
std::vector<SpriteSet*> Guard::MOVE_ANIMATIONS;

void Guard::Load() {
    MOVE_SPRITE_SHEET = new SpriteSheet("charset/guard/move.png", 100, 160, 50, 40);
    MOVE_SPRITE_SHEET->set_hit_spritesheet("charset/guard/move_hit.png");
    MOVE_ANIMATIONS = {
            new SpriteSet(MOVE_SPRITE_SHEET->GetSprites(0, 2), 0, 100, vec2f(-16.0f, -12.0f)),
            new SpriteSet(MOVE_SPRITE_SHEET->GetSprites(1, 2), 0, 100, vec2f(-16.0f, -12.0f)),
            new SpriteSet(MOVE_SPRITE_SHEET->GetSprites(2, 2), 0, 200, vec2f(-16.0f, -12.0f)),
            new SpriteSet(MOVE_SPRITE_SHEET->GetSprites(3, 2), 0, 150, vec2f(-16.0f, -12.0f))
    };
}

Guard::Guard(Level* level) :
        super(
                level,
                0.0f, 0.0f, 18.0f, 14.0f,
                new ::Move(this, MOVE_ANIMATIONS)
        )
{
    speed_ = 50;
}

void Guard::Update(double delta) {
    super::Update(delta);

    /*AnimationHitbox* hitbox = new AnimationHitbox(position_, current_action_->CurrentAnimation());
    MeleeAttack(hitbox);
    delete hitbox;*/
}
