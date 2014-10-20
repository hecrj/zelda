#include "mob.hpp"

Mob::Mob(const char *name, Level* level, float x, float y, float width, float height, Action* idle_action) :
        super(name, x, y, width, height),
        level_(level),
        facing_(Dir::UP),
        facing_candidate_(-1),
        moving_(false),
        idle_action_(idle_action),
        current_action_(idle_action)
{}

void Mob::set_AI(AI* ai) {
    ai_ = ai;
}

void Mob::ChangeAction(Action* action)
{
    current_action_->Leave();
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
    return alive() && !current_action_->IsBlocking();
}

void Mob::Move(Dir direction, double delta) {
    vec2f new_position = position_ + direction.vector() * delta * 80;

    if(facing_.index() == direction.index() || facing_candidate_ == -1) {
        facing_candidate_ = direction.index();
    }

    if(!level_->IsInbounds(new_position, width_, height_)) {
        return;
    }

    vec2f old_position = position_;
    position_ = new_position;

    std::vector<Rectangle*> collidables;
    level_->CollidablesFor(this, collidables);

    for(Rectangle* collidable : collidables) {
        if(collidable != this && CanCollideWith(collidable) && CollidesWith(collidable)) {
            position_ = old_position;
            return;
        }
    }

    moving_ = true;
}

void Mob::Update(double delta) {
    if(CanMove())
        ai_->Update(delta);

    if(facing_candidate_ != -1) {
        facing_ = *Dir::ALL[facing_candidate_];
        facing_candidate_ = -1;
    }

    if(current_action_->IsFinished())
        ChangeAction(idle_action_);

    current_action_->Update(delta);

    super::Update(delta);
    moving_ = false;
}

void Mob::Render() const {
    current_action_->Render();

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
