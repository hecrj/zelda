#include "../mob.hpp"
#include "../../graphic/spritesheet.hpp"

class Link : public Mob {
public:
    typedef Mob super;

    static SpriteSheet* const MOVE_SPRITE_SHEET;
    static const std::vector<Animation*> MOVE_ANIMATIONS;

    Link(Level* level);
};
