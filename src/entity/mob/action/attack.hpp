#include "../action.hpp"
#include "../../../graphic/animation.hpp"
#include "../../../math/rectangle.hpp"
#include "../../../graphic/hitbox/hidden_hitbox.hpp"

class Attack : public Action {
public:
    typedef Action super;
    Attack(Mob* mob, const std::vector<Animation*>& animations);

    void Enter();
    void Leave();

private:
    HiddenHitbox* hitbox_;
};
