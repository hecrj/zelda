#include "../action.hpp"
#include "../../../graphic/animation.hpp"

class Move : public Action {
public:
    typedef Action super;
    Move(Mob* mob, const std::vector<SpriteSet*>& animations);

    bool IsBlocking() const;
    bool IsFinished() const;
    void Update(double delta);
};
