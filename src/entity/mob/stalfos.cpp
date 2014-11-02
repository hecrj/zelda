#include "stalfos.hpp"

#include "action/move.hpp"
#include "ai/chase_evade.hpp"
#include "../../graphic/effect/rotation_fade.hpp"
#include "../../map/level.hpp"
#include "../item/key.hpp"

SpriteSheet* Stalfos::MOVE_SPRITE_SHEET;
std::vector<SpriteSet*> Stalfos::MOVE_ANIMATIONS;

void Stalfos::Load() {
    MOVE_SPRITE_SHEET = new SpriteSheet("charset/stalfos/move.png", 36, 144, 18, 36);
    MOVE_ANIMATIONS = {
            new SpriteSet(MOVE_SPRITE_SHEET->GetSprites(0, 2), 0, 100, vec2f(-3.0f, -16.0f)),
            new SpriteSet(MOVE_SPRITE_SHEET->GetSprites(1, 2), 0, 100, vec2f(-3.0f, -16.0f)),
            new SpriteSet(MOVE_SPRITE_SHEET->GetSprites(2, 2), 0, 200, vec2f(-3.0f, -16.0f)),
            new SpriteSet(MOVE_SPRITE_SHEET->GetSprites(3, 2), 0, 150, vec2f(-3.0f, -16.0f))
    };
}

Stalfos::Stalfos(const std::string& name, float x, float y, bool small_key, bool boss_key) :
        super(
                x, y, 14.0f, 14.0f,
                new ::Move(this, MOVE_ANIMATIONS)
        ),
        name_(name),
        small_key_(small_key),
        boss_key_(boss_key)
{
    speed_ = 50;
    type_ = ENEMY;
    health_ = 5;
    die_effect_ = new RotationFade();
    set_AI(new ChaseEvade(this));
}

void Stalfos::Dead() {
    vec2f pos = center();

    Link* player = (Link*)level_->main_player();

    if(small_key_) {
        if(not player->has_key(name_)) {
            level_->AddEntity(new Key(Key::SMALL, name_, pos.x, pos.y));
        }
    } else if(boss_key_) {
        if(not player->has_key(name_)) {
            level_->AddEntity(new Key(Key::BOSS, name_, pos.x, pos.y));
        }
    } else {
        super::Dead();
    }
}
