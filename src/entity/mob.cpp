#include <iostream>
#include "mob.hpp"
#include "mob/action/push.hpp"
#include "../map/level.hpp"
#include "../map/path.hpp"
#include "../debug.hpp"

Mob::Mob(Level* level, float x, float y, float width, float height, Action* idle_action) :
        super(x, y, width, height, 100),
        level_(level),
        facing_(Dir::UP),
        facing_candidate_(-1),
        moving_(false),
        idle_action_(idle_action),
        current_action_(idle_action),
        speed_(60)
{}

Mob::~Mob() {
    delete ai_;
    delete idle_action_;

    for(auto& action : actions_) {
        delete action.second;
    }
}

void Mob::set_AI(AI* ai) {
    ai_ = ai;
}

void Mob::ChangeAction(Action* action)
{
    current_action_->Leave();

    if(current_action_->IsTemporary())
        delete current_action_;

    current_action_ = action;
    current_action_->Enter();
}

const Dir& Mob::facing() const {
    return facing_;
}

bool Mob::moving() const {
    return moving_;
}

bool Mob::CanMove() const {
    return IsAlive() && !current_action_->IsBlocking();
}

void Mob::Move(const Dir& direction, double delta) {
    if(facing_.index() == direction.index() || facing_candidate_ == -1) {
        facing_candidate_ = direction.index();
    }

    _Move(direction.vector(), 1, delta);
}

void Mob::Slide(const vec2f direction, int intensity, double delta) {
    _Move(vec2f(direction.x, 0), intensity, delta);
    _Move(vec2f(0, direction.y), intensity, delta);
}

void Mob::Update(double delta) {
    moving_ = false;

    if(current_action_->IsFinished())
        ChangeAction(idle_action_);

    if(CanMove()) {
        ai_->Move(delta);

        if(facing_candidate_ != -1) {
            facing_ = *Dir::ALL[facing_candidate_];
            facing_candidate_ = -1;
        }

        ai_->Update(delta);
    }

    current_action_->Update(delta);
    super::Update(delta);
}

void Mob::Render() const {
    current_action_->Render();

    if(Debug::enabled)
        ai_->Debug();

    super::Render();
}

Action* Mob::action(std::string name) const {
    std::map<std::string, Action*>::const_iterator it = actions_.find(name);

    if(it == actions_.end())
        return 0;
    else
        return it->second;
}

void Mob::RegisterAction(std::string name, Action *action) {
    actions_[name] = action;
}

void Mob::MeleeAttack(Hitbox* hitbox) {
    std::vector<Rectangle*> candidates;
    level_->DynamicCollidablesFor(hitbox, candidates);

    for(Rectangle* candidate : candidates) {
        if(candidate->CanCollideWith(hitbox) && hitbox->CollidesWith(candidate)) {
            Collision c = hitbox->CollisionType(candidate);

            if(c == Collision::DAMAGE) {
                // TODO: Make dynamic collidables a Quadtree of entities
                if(candidate->IsEntity()) {
                    ((Entity*)candidate)->Damage(this, 10);
                }
                std::cout << "Melee attack collision" << std::endl;
            }
        }
    }
}

void Mob::Damage(Entity* from, int damage) {
    super::Damage(from, damage);

    if(!current_action_->IsTemporary()) {
        vec2f dir = center() - from->center();
        dir.normalize();

        ChangeAction(new Push(this, idle_action_, dir, damage, 0.1f));
    }
}

bool Mob::IsMob() const {
    return true;
}

Sprite *Mob::CurrentSprite(vec2f &position) const {
    Animation* animation =  current_action_->CurrentAnimation();
    position = animation->position();

    return animation->CurrentSprite();
}

Sprite *Mob::CurrentSprite() const {
    return current_action_->CurrentAnimation()->CurrentSprite();
}

bool Mob::FollowPath(Path* path, double delta) {
    if(path->nodes.empty())
        return false;

    vec2i next;
    float dist;
    vec2f pos(x() / Path::RESOLUTION, y() / Path::RESOLUTION);

    while(path->nodes.size() > 0) {
        next = path->nodes.back();
        dist = pos.dist(vec2f(next.x, next.y));

        if(dist > 1)
            break;

        path->nodes.pop_back();
    }

    _MoveVector(vec2f(next.x, next.y) - pos, delta);

    vec2f dir = path->to->center() - path->from->center();

    if(std::abs(dir.x) > std::abs(dir.y))
        dir.y = 0;
    else
        dir.x = 0;

    facing_candidate_ = Dir::fromVector(dir).index();
    return true;
}

void Mob::MoveTowards(Entity* entity, double delta) {
    _MoveVector(entity->center() - center(), delta);
}

Entity* Mob::SeekPlayer() const {
    // TODO: Check distance and range of vision
    return level_->players()[0];
}

Path* Mob::FindPath(Entity* to) {
    return level_->FindPath(this, to);
}

void Mob::_MoveVector(vec2f dir, double delta) {
    if(dir.x == 0 || dir.y == 0) {
        _Move(Dir::fromVector(dir).vector(), 1, delta);
    } else {
        float x = dir.x;
        float y = dir.y;

        dir.x = 0;

        if(std::abs(y) < 0.5)
            _Move(dir, 1, delta);
        else
            _Move(Dir::fromVector(dir).vector(), 1, delta);

        dir.x = x;
        dir.y = 0;

        if(std::abs(x) < 0.5)
            _Move(dir, 1, delta);
        else
            _Move(Dir::fromVector(dir).vector(), 1, delta);
    }
}

bool Mob::_Move(const vec2f& direction, int intensity, double delta) {
    vec2f new_position = position_ + direction * intensity * delta * speed_;

    if(!level_->IsInbounds(new_position, width_, height_)) {
        return false;
    }

    vec2f old_position = position_;
    position_ = new_position;

    std::vector<Rectangle*> collidables;
    level_->CollidablesFor(this, collidables);

    for(Rectangle* collidable : collidables) {
        if(CanCollideWith(collidable) && CollidesWith(collidable)) {
            // TODO: Handle collisions
            position_ = old_position;
            return false;
        }
    }

    moving_ = true;
    return true;
}
