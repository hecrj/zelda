#pragma once

#include <tmx_map.hpp>
#include "../math/rectangle.hpp"
#include "../map/level.hpp"

class Event : public RectangleShape {
public:
    typedef RectangleShape super;
    Event(Level* level, float x, float y, float width, float height);

    bool CanCollideWith(RectangleShape* rectangle) const;

protected:
    Level* level_;
};
