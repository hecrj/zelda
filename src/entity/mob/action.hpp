#pragma once

#include <string>

class Mob;
class Action {
public:
    Action(const char* name, Mob* mob);

    virtual bool IsBlocking() const;
    virtual bool IsFinished() const;

    virtual void Enter();
    virtual void Leave();
    virtual void Update(double delta);
    void Render() const;

protected:
    Mob* mob_;

private:
    std::string name_;
};
