#include "link.hpp"
#include "action/move.hpp"
#include "action/attack.hpp"
#include "../../audio/sound.hpp"
#include "../../graphic/effect/blink.hpp"
#include "../../map/level.hpp"
#include "../../graphic/effect/fade.hpp"
#include "../../audio/music.hpp"
#include "../../game.hpp"

SpriteSheet* Link::MOVE_SPRITE_SHEET;
std::vector<SpriteSet*> Link::MOVE_ANIMATIONS;
SpriteSheet* Link::ATTACK_SPRITE_SHEET;
std::vector<SpriteSet*> Link::ATTACK_ANIMATIONS;
sf::SoundBuffer* Link::ATTACK_SOUND;
sf::SoundBuffer* Link::HURT_SOUND;
sf::SoundBuffer* Link::DIE_SOUND;

void Link::Load() {
    MOVE_SPRITE_SHEET = new SpriteSheet("charset/link/move_shield.png", 147, 108, 21, 27);
    ATTACK_SPRITE_SHEET = new SpriteSheet("charset/link/attack_sword.png", 324, 144, 36, 36);

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
    DIE_SOUND = Sound::Buffer("link/dies.wav");
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
    die_sound_ = DIE_SOUND;

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

int Link::small_keys() const {
    return small_keys_;
}

int Link::boss_keys() const {
    return boss_keys_;
}

bool Link::CollidesWith(Rectangle const * rectangle) const {
    return super::CollidesWith(rectangle) and (
            (not rectangle->IsEntity()) or
            ((Entity*)rectangle)->type() != ENEMY or
            is_vulnerable_ and (
                ((Entity*)rectangle)->type() != BOSS or
                rectangle->CollidesWith(this)
            )
    );
}

bool Link::HandleCollisionWith(Mob* mob) {
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

void Link::UpdateSmallKeys(int keys) {
    small_keys_ += keys;
}

void Link::UpdateBossKeys(int keys) {
    boss_keys_ += keys;
}

bool Link::has_key(const std::string& name) const {
    return keys_.find(name) != keys_.end();
}

void Link::AddSmallKey(std::string const& name) {
    small_keys_++;
    keys_[name] = true;
}

void Link::AddBossKey(const std::string& name) {
    boss_keys_++;
    keys_[name] = true;
}

bool Link::CanCollideWith(Rectangle *rectangle) const{
    return super::CanCollideWith(rectangle) and (
            not rectangle->IsEntity() or
            ((Entity*) rectangle)->type() != FOLLOWER
    );
}

void Link::Damage(Entity* from, int amount) {
    super::Damage(from, amount);

    if(is_vulnerable_) {
        is_vulnerable_ = false;
        ChangeEffect(new Blink(3, 0.1, [this] {
            is_vulnerable_ = true;
        }));
    }
}

void Link::Die() {
    super::Die();

    Music::ClearQueue();
    Music::FadeOut(1);
    level_->ChangeEffect(new Fade(Fade::OUT, 1, [this]{
        Game::INSTANCE.Over(level_->name());
    }));
}
