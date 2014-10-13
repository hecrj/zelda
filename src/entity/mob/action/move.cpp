#include "move.hpp"
#include "../../mob.hpp"

Move::Move(Mob* mob) : super("move", mob) {

}

bool Move::IsBlocking() const {
    return false;
}