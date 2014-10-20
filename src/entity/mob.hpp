#pragma once

#include "../entity.hpp"
#include "../map/level.hpp"
#include "mob/action.hpp"
#include "mob/ai.hpp"
#include "../math/vec2.hpp"
#include "../math/dir.hpp"
#include <map>
#include <string>

class Mob : public Entity {
public:
    typedef Entity super;
    Mob(Level* level, float x, float y, float width, float height, Action* idle_action_);

    bool CanMove() const;
    const Dir& facing() const;
    bool moving() const;
    Action* action(std::string name) const;
    Hitmap *GetHitmap() const;

    void set_AI(AI* ai);
    void RegisterAction(std::string name, Action *action);
    void ChangeAction(Action *action);
    void Move(Dir direction, double delta);
    void Attach(Rectangle* e);
    void Unattach(Rectangle* e);

    void Update(double delta);
    void Render() const;


private:
    Level* level_;
    AI* ai_;
    Action* idle_action_;
    Action* current_action_;
    std::map<std::string, Action*> actions_;
    Dir facing_;
    int facing_candidate_;
    bool moving_;
};
