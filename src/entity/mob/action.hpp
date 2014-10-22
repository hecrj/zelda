#pragma once

#include <string>
#include <vector>
#include "../../graphic/animation.hpp"

class Mob;
class Action {
public:
    Action(Mob* mob, const std::vector<SpriteSet*>& spritesets);
    Action(Mob* mob, const std::vector<Animation*>& animations);

    const std::vector<Animation*>& animations() const;
    virtual bool IsBlocking() const;
    virtual bool IsFinished() const;
    virtual bool IsTemporary() const;
    Animation* CurrentAnimation() const;

    virtual void Enter();
    virtual void Leave();
    virtual void Update(double delta);
    void Render() const;

protected:
    Mob* mob_;

private:
    std::vector<Animation*> animations_;
};
