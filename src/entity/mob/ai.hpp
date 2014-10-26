#pragma once

class Mob;
class Path;
class AI {
public:
    AI(Mob* mob);

    Path* FindPlayer() const;

    virtual void Move(double delta);
    virtual void Update(double delta);
    virtual void Debug() const;

protected:
    Mob* mob_;
};
