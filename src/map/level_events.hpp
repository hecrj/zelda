#pragma once

#include <string>
#include <map>
#include "level.hpp"

class LevelEvents {
public:
    typedef void (*MapEvent)(Level*);
    LevelEvents();

    void Register(const std::string& name, MapEvent event);
    MapEvent event(const std::string& name) const;

private:
    std::map<std::string, MapEvent> events_;
};