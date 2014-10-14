#include "../mob.hpp"

class Link : public Mob {
public:
    typedef Mob super;

    static const std::vector<Animation*> MOVE_ANIMATIONS;

    Link(Level* level);
};
