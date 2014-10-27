#pragma once

#include <tmx_map.hpp>
#include "../math/rectangle.hpp"
#include "../entity.hpp"
#include "../math/dir.hpp"

class Location : public Rectangle {
public:
    typedef Rectangle super;
    Location(float x, float y, float width, float height, const std::string& orientation);
    Location(const TMX::Object& object);

    void Place(Entity* entity) const;

private:
    int xdir;
    int ydir;

    void set_orientation(const std::string& orientation);
};
