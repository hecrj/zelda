#pragma once

#include "../entity.hpp"
#include "mob/action.hpp"
#include "mob/ai.hpp"
#include "../math/vec2.hpp"
#include "../math/dir.hpp"
#include <map>
#include <string>

class Level;
class Path;
class Mob : public Entity {
public:
    typedef Entity super;
    Mob(Level* level, float x, float y, float width, float height, Action* idle_action_);
    ~Mob();

    bool CanMove() const;
    const Dir& facing() const;
    bool moving() const;
    bool IsMob() const;
    Action* action(std::string name) const;
    Sprite* CurrentSprite(vec2f& position) const;
    Sprite* CurrentSprite() const;
    Entity* SeekPlayer() const;
    Path* FindPath(Entity* to);
    bool FollowPath(Path* path, double delta);

    void set_AI(AI* ai);
    void RegisterAction(std::string name, Action *action);
    void ChangeAction(Action *action);
    void Move(const Dir& direction, double delta);
    void MoveTowards(Entity* entity, double delta);
    void Slide(const vec2f direction, int intensity, double delta);
    void MeleeAttack(Hitbox* hitbox);
    void Damage(Entity* from, int damage);

    void Update(double delta);
    void Render() const;

protected:
    Action* idle_action_;
    Action* current_action_;
    float speed_;

private:
    Level* level_;
    AI* ai_;
    std::map<std::string, Action*> actions_;
    Dir facing_;
    int facing_candidate_;
    bool moving_;

    bool _Move(const vec2f& direction, int intensity, double delta);
    void _MoveVector(vec2f dir, double delta);
};
