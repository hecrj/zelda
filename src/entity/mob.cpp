#include "mob.hpp"

Mob::Mob(const char *name, Level* level, vec2f top_left, vec2f bottom_right) :
        super(name, top_left, bottom_right),
        level_(level),
        facing(Dir::UP),
        moving(false)
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
    return alive() && !current_action_->isBlocking();
}

void Mob::Update(float delta) {
    if(CanMove())
        ai_->Update(delta);

    super::Update(delta);
}

void Mob::Render() const {
    current_action_->Render();
}
