#include "../action.hpp"

class Move : public Action {
public:
    typedef Action super;
    Move(Mob* mob);

    bool IsBlocking() const;
};