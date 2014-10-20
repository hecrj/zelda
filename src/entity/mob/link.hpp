#include "../mob.hpp"
#include "../../graphic/spritesheet.hpp"

class Link : public Mob {
public:
    typedef Mob super;

    static SpriteSheet* MOVE_SPRITE_SHEET;
    static SpriteSheet* ATTACK_SPRITE_SHEET;

    static std::vector<Animation*> MOVE_ANIMATIONS;
    static std::vector<Animation*> ATTACK_ANIMATIONS;

    Link(Level* level);
    static void Load();
};
