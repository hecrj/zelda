#pragma once

class Mob;
class AI {
public:
    AI(Mob* mob);
    virtual void Move(double delta);
    virtual void Update(double delta);
    virtual void Debug() const;

protected:
    Mob* mob_;
};
