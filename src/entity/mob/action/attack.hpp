#include "../action.hpp"
#include "../../../graphic/animation.hpp"

class Attack : public Action {
    public:
    typedef Action super;
    Attack(Mob* mob, const std::vector<Animation*>& animations);

    void Update(double delta);
};
