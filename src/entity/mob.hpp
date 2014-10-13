#pragma once

#include "../entity.hpp"
#include "../map/level.hpp"
#include "mob/action.hpp"
#include "mob/ai.hpp"
#include "../math/vec2.hpp"
#include "../math/dir.hpp"

class Mob : public Entity {
public:
    typedef Entity super;
    Mob(const char* name, Level* level, vec2f top_left, vec2f bottom_right);

    void set_AI(AI* ai);
    void ChangeAction(Action *action);
    bool CanMove() const;
    void Update(float delta);
    void Render() const;

private:
    Level* level_;
    AI* ai_;
    Action* current_action_;
    Dir facing;
    bool moving;
};
