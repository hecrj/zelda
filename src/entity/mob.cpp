#include "mob.hpp"

Mob::Mob(const char *name, Level* level, vec2f top_left, vec2f bottom_right, Action* idle_action) :
        super(name, top_left, bottom_right),
        level_(level),
        facing_(Dir::UP),
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

bool Mob::CanMove() const {
    return alive() && !current_action_->IsBlocking();
}

void Mob::Move(Dir direction, double delta) {
    vec2f new_position = position_ + (direction.vector() * delta * 100);

    // TODO: Check level collisions
    position_ = new_position;
}

void Mob::Update(double delta) {
    if(CanMove())
        ai_->Update(delta);

    if(current_action_->IsFinished())
        ChangeAction(idle_action_);

    current_action_->Update(delta);

    super::Update(delta);
}

void Mob::Render() const {
    current_action_->Render();
}
