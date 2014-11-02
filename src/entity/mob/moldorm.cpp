#include "moldorm.hpp"
#include "action/move.hpp"
#include "ai/rotation_chase.hpp"
#define _USE_MATH_DEFINES
#include "math.h"
#include "../../debug.hpp"

SpriteSheet* Moldorm::SPRITESHEET;
SpriteSet* Moldorm::HEAD;
Sprite* Moldorm::MIDDLE1;
Sprite* Moldorm::MIDDLE2;
Sprite* Moldorm::MIDDLE3;
Sprite* Moldorm::TAIL;

void Moldorm::Load() {
    SPRITESHEET = new SpriteSheet("charset/moldorm/body.png", 32, 150, 32, 30);
    TAIL = SPRITESHEET->GetSprites(0, 1)[0];
    MIDDLE1 = SPRITESHEET->GetSprites(1, 1)[0];
    MIDDLE2 = SPRITESHEET->GetSprites(2, 1)[0];
    MIDDLE3 = SPRITESHEET->GetSprites(3, 1)[0];
    HEAD = new SpriteSet(SPRITESHEET->GetSprites(4, 1), 0, 30, vec2f(49, 50));
}

Moldorm::Moldorm(float x, float y, Level* level) :
        super(x, y, 32, 32, new ::Move(this, {HEAD})),
        hitbox_(new MoldormHitbox(this))
{
    set_AI(new RotationChase(this));
    type_ = BOSS;
    is_vulnerable_ = false;
    facing_ = Dir::DOWN;
    rotation = 0;

    MoldormNode* middle1 = new MoldormNode(x, y, 17, 15, vec2f(-8, -8), 18, MIDDLE3, this, this);
    MoldormNode* middle2 = new MoldormNode(x, y, 17, 15, vec2f(-8, -8), 13, MIDDLE2, this, middle1);
    MoldormNode* middle3 = new MoldormNode(x, y, 12, 12, vec2f(-10, -10), 12, MIDDLE1, this, middle2);
    MoldormNode* tail = new MoldormNode(x, y, 16, 16, vec2f(-8, -8), 12, TAIL, this, middle3);

    nodes_.push_back(tail);
    nodes_.push_back(middle3);
    nodes_.push_back(middle2);
    nodes_.push_back(middle1);

    level->AddCollidable(hitbox_);
}

void Moldorm::Update(double delta) {
    super::Update(delta);
    facing_ = Dir::DOWN;
    float angle = rotation * (float)M_PI / 180;
    vec2f direction = vec2f((float)-sin(angle), (float)cos(angle));

    if(Move(direction, 1, delta)) {
        hitbox_->set_position(position_.x - 49, position_.y - 50);

        for(MoldormNode* node : nodes_)
            node->Update(delta);
    } else {
        rotation = (rotation + 180) % 360;
    }
}

void Moldorm::Draw() const {
    for(MoldormNode* node : nodes_)
        node->Render();

    glPushMatrix();
    glTranslatef(position_.x + 16, position_.y + 15, 0);
    glRotatef(rotation, 0, 0, 1.0f);
    CurrentSprite()->Render(vec2f(-16, -15));
    glPopMatrix();

    if(Debug::enabled) {
        for(MoldormNode* node : nodes_)
            node->DrawBox(0, 0, 1);

        hitbox_->DrawBox(0, 0, 1);
    }
}

bool Moldorm::CanCollideWith(Rectangle* rectangle) const {
    return rectangle != hitbox_ and (not rectangle->IsEntity() or ((Entity*)rectangle)->type() == PLAYER);
}

bool Moldorm::CollidesWith(Rectangle const * rectangle) const {
    if(rectangle->IsEntity()) {
        for(MoldormNode* node : nodes_) {
            if(node->CollidesWith(rectangle))
                return true;
        }
    }

    return super::CollidesWith(rectangle);
}

Moldorm::MoldormNode::MoldormNode(float x, float y, float width, float height, const vec2f& offset, float max_distance,
        Sprite* sprite, Moldorm* head, Rectangle* parent) :
        super(x, y, width, height),
        offset_(offset),
        max_distance_(max_distance),
        sprite_(sprite),
        head_(head),
        parent_(parent)
{}

void Moldorm::MoldormNode::Update(double delta) {
    if(parent_->Distance(this) > max_distance_) {
        vec2f dir = parent_->center() - center();
        dir.normalize();
        dir = dir * head_->speed() * delta;

        set_position(position_.x + dir.x, position_.y + dir.y);
    }
}

void Moldorm::MoldormNode::Draw() const {
    sprite_->Render(position_ + offset_);
}

Moldorm::MoldormHitbox::MoldormHitbox(Moldorm* moldorm) :
        super(moldorm->position().x - 49, moldorm->position().y - 50, 130, 130),
        moldorm_(moldorm)
{}

bool Moldorm::MoldormHitbox::CanCollideWith(Rectangle* rectangle) const {
    return moldorm_ != rectangle and moldorm_->CollidesWith(rectangle);
}

bool Moldorm::HandleCollisionWith(Mob* mob) {
    mob->Damage(this, 2);
    return true;
}

bool Moldorm::MoldormHitbox::HandleCollisionWith(Mob* mob) {
    return moldorm_->HandleCollisionWith(mob);
}
