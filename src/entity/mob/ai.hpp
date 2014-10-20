#pragma once

class Mob;
class AI {
public:
    AI(Mob* mob);
    virtual void Move(double delta) = 0;
    virtual void Update(double delta) = 0;

protected:
    Mob* mob_;
};
