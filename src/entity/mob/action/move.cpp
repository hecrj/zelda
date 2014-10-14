#include "move.hpp"
#include "../../mob.hpp"

Move::Move(Mob* mob, const std::vector<Animation*>& animations) : super("move", mob, animations) {

}

bool Move::IsBlocking() const {
    return false;
}
