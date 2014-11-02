#pragma once

class Mob;
class Path;
class AI {
public:
    AI(Mob* mob);

    Path* PathToPlayer() const;
    Path* PathToEnemy() const;

    virtual void Update(double delta);
    virtual void Debug() const;

protected:
    Mob* mob_;
};
