#pragma once

#include <string>
#include <vector>
#include "../../graphic/animation.hpp"

class Mob;
class Action {
public:
    Action(const char* name, Mob* mob, const std::vector<SpriteSet*>& animations);

    virtual bool IsBlocking() const;
    virtual bool IsFinished() const;
    Animation* CurrentAnimation() const;

    virtual void Enter();
    virtual void Leave();
    virtual void Update(double delta);
    void Render() const;

protected:
    Mob* mob_;

private:
    std::string name_;
    std::vector<Animation*> animations_;
};
