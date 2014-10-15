#include "../action.hpp"
#include "../../../graphic/animation.hpp"

class Move : public Action {
public:
    typedef Action super;
    Move(Mob* mob, const std::vector<Animation*>& animations);

    bool IsBlocking() const;
    void Update(double delta);
};
