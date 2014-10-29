#pragma once

#include "../event.hpp"

class MapTransition : public Event {
public:
    typedef Event super;
    MapTransition(Level* level, float x, float y, float width, float height, const std::string& name,
            const std::string& orientation, const std::string& map, const std::string& place);

    bool HandleCollisionWith(Mob* mob);

private:
    std::string map_;
    std::string place_;
};