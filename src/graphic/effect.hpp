#pragma once

class Effect {
public:
    Effect();

    virtual bool IsFinished() const = 0;

    virtual void Update(double delta) = 0;
    virtual void Render() const = 0;
};
