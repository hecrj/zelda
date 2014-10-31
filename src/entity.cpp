#include "entity.hpp"
#include "map/level.hpp"
#include "debug.hpp"
#include "audio/sound.hpp"

Entity::Entity(float x, float y, float width, float height) :
        super(x, y, width, height),
        health_(20),
        type_(UNKNOWN),
        die_effect_(0),
        hurt_sound_(0),
        die_sound_(0)
{}

Entity::~Entity() {
    if(die_effect_)
        delete die_effect_;
}

bool Entity::IsAlive() const {
    return health_ > 0;
}

void Entity::Kill() {
    health_ = 0;
}

bool Entity::moving() const {
    return false;
}

bool Entity::IsEntity() const {
    return true;
}

int Entity::health() const {
    return health_;
}

void Entity::Damage(Entity* from, int damage) {
    Sound::Play(hurt_sound_);
    health_ -= damage;
}

bool Entity::IsMob() const {
    return false;
}

bool Entity::SortByYCoordinateAsc::operator()(Entity* e1, Entity* e2) const {
    return e1->y() < e2->y() or (e1->y() == e2->y() and e1->x() < e2->x());
}

float Entity::Distance(Entity* entity) const {
    return center().dist(entity->center());
}

EntityType Entity::type() const {
    return type_;
}

bool Entity::IsFinallyDead() const {
    return not current_effect_ or current_effect_->IsFinished();
}

void Entity::Dead() {
    // Do nothing
}

void Entity::Die() {
    Sound::Play(die_sound_);

    if(die_effect_) {
        ChangeEffect(die_effect_);
        die_effect_ = 0;
    }
}

void Entity::set_level(Level* level) {
    level_ = level;
}

void Entity::NotifyCollisions() {
    std::vector<Rectangle*> collidables;
    level_->CollidablesFor(this, collidables);

    for(Rectangle* collidable : collidables) {
        if(collidable->IsEntity() && ((Entity*)collidable)->IsMob()) {
            Mob* mob = (Mob*)collidable;

            if(CanCollideWith(mob) && CollidesWith(mob)) {
                if(HandleCollisionWith(mob)) {
                    return;
                }
            }
        }
    }
}

bool Entity::IsVulnerable() const {
    return true;
}
