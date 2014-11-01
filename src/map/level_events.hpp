#pragma once

#include <string>
#include <map>
#include "level.hpp"

class LevelEvents {
public:
    typedef void (* LevelEvent)(Level*);
    LevelEvents();

    void Register(const std::string& name, LevelEvent event);
    LevelEvent event(const std::string& name) const;

private:
    std::map<std::string, LevelEvent> events_;
};