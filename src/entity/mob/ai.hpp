#pragma once

class Mob;
class AI {
public:
    AI(Mob* mob);
    virtual void Update(float delta) = 0;

protected:
    Mob* mob_;
};
