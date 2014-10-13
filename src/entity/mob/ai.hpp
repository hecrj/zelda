#pragma once

class Mob;
class AI {
public:
    AI(Mob* mob);
    virtual void Update(double delta) = 0;

protected:
    Mob* mob_;
};
