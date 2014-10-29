#pragma once

#include <tmx_map.hpp>
#include "../math/rectangle.hpp"
#include "../map/level.hpp"

class Event : public Rectangle {
public:
    typedef Rectangle super;
    Event(Level* level, float x, float y, float width, float height);

    bool CanCollideWith(Rectangle* rectangle) const;

protected:
    Level* level_;
};
