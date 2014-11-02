#include "linkfollower.hpp"
#include "action/move.hpp"
#include "action/attack.hpp"
#include "../../audio/sound.hpp"
#include "ai/follower.hpp"
#include "../../graphic/effect/rotation_fade.hpp"
#include "../../graphic/hitbox/animation_hitbox.hpp"

SpriteSheet* LinkFollower::MOVE_SPRITE_SHEET;
std::vector<SpriteSet*> LinkFollower::MOVE_ANIMATIONS;
SpriteSheet* LinkFollower::ATTACK_SPRITE_SHEET;
std::vector<SpriteSet*> LinkFollower::ATTACK_ANIMATIONS;
sf::SoundBuffer* LinkFollower::ATTACK_SOUND;
sf::SoundBuffer* LinkFollower::HURT_SOUND;

void LinkFollower::Load() {
    MOVE_SPRITE_SHEET = new SpriteSheet("charset/follower/move_shield.png", 147, 108, 21, 27);
    ATTACK_SPRITE_SHEET = new SpriteSheet("charset/follower/attack_sword.png", 324, 144, 36, 36);

    MOVE_ANIMATIONS = {
            new SpriteSet(MOVE_SPRITE_SHEET->GetSprites(0, 7), 3, vec2f(0.0f, -12.0f), {20, 30, 40, 30, 40, 30, 20}),
            new SpriteSet(MOVE_SPRITE_SHEET->GetSprites(1, 7), 3, vec2f(0.0f, -12.0f), {20, 30, 40, 30, 40, 30, 20}),
            new SpriteSet(MOVE_SPRITE_SHEET->GetSprites(2, 7), 3, vec2f(0.0f, -12.0f), {20, 30, 40, 30, 40, 30, 20}),
            new SpriteSet(MOVE_SPRITE_SHEET->GetSprites(3, 7), 3, vec2f(0.0f, -12.0f), {20, 30, 40, 30, 40, 30, 20})
    };

    MOVE_ANIMATIONS[Dir::DOWN.index()]->ping_pong = true;
    MOVE_ANIMATIONS[Dir::UP.index()]->ping_pong = true;

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

LinkFollower::LinkFollower(float x, float y) :
        super(
                x, y, 18.0f, 14.0f,
                new ::Move(this, MOVE_ANIMATIONS)
        )
{
    speed_ = 50;
    type_ = PLAYER;
    set_AI(new Follower(this));
    RotationFade* die_effect = new RotationFade();
    die_effect->set_drawable(this);
    this->SetDieEffect(die_effect);

    attack_sound_ = ATTACK_SOUND;
    hurt_sound_ = HURT_SOUND;
    AddAction("attack", new Attack(this, ATTACK_ANIMATIONS));
}

bool LinkFollower::CollidesWith(Rectangle const * rectangle) const {
    return super::CollidesWith(rectangle) and (
            not rectangle->IsEntity() or
            ((Entity*)rectangle)->type() != BOSS or
            rectangle->CollidesWith(this)
    );
}

bool LinkFollower::HandleCollisionWith(Mob* mob) {
    switch(mob->type()) {
        case ENEMY:
            Damage(mob, 2);
            break;

        case BOSS:
            Damage(mob, 4);
            break;

        default:
            break;
    }
}
