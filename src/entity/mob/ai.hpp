#pragma once

class Mob;
class Path;
class AI {
public:
    AI(Mob* mob);

    Path* FindPlayer() const;
    void UpdatePath(Path*& path, double delta);

    virtual void Move(double delta);
    virtual void Update(double delta);
    virtual void Debug() const;

protected:
    Mob* mob_;

private:
    Path* temp_path_;
};
