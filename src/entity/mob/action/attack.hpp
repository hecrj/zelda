#include "../action.hpp"
#include "../../../graphic/animation.hpp"
#include "../../../math/rectangle.hpp"
#include "../../../graphic/hitbox/animation_hitbox.hpp"

class Attack : public Action {
public:
    typedef Action super;
    Attack(Mob* mob, const std::vector<SpriteSet*>& animations);

    void Enter();
    void Leave();

private:
    AnimationHitbox * hitbox_;
};
