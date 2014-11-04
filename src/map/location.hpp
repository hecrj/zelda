#pragma once

#include <tmx_map.hpp>
#include "../math/rectangle.hpp"
#include "../entity.hpp"
#include "../math/dir.hpp"

class Location : public RectangleShape {
public:
    typedef RectangleShape super;
    Location(float x, float y, float width, float height, const std::string& name, const std::string& orientation);

    void Place(Entity* entity) const;
    const std::string& name() const;

private:
    std::string name_;
    int xdir;
    int ydir;

    void set_orientation(const std::string& orientation);
};
