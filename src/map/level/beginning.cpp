#include "beginning.hpp"
#include "../level.hpp"

namespace BeginningEvents {
    void close_room(Level *level) {

    }
}

Beginning::Beginning() {
    Register("close_room", &BeginningEvents::close_room);
}
