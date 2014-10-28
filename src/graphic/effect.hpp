#pragma once

class Entity;
class Effect {
public:
    Effect(Entity* entity);

    virtual bool IsFinished() const = 0;

    virtual void Update(double delta) = 0;
    virtual void Render() const = 0;

protected:
    Entity* entity_;
};
