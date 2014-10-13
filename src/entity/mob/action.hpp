#pragma once

class Action {
public:
    Action(const char* name);

    virtual bool isBlocking() const;
    virtual bool isFinished() const;

    virtual void Enter();
    virtual void Leave();
    void Update(float delta);
    void Render() const;
};
