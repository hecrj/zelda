#include "../ai.hpp"
#include "../action.hpp"

class Player : public AI {
public:
    typedef AI super;
    Player(Mob* mob, bool* keys);

    void Update(double delta);

private:
    bool* keys_;
    Action* attack_;
};
