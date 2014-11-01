#include "level_events.hpp"

LevelEvents::LevelEvents() {

}

void LevelEvents::Register(const std::string& name, LevelEvent event) {
    events_[name] = event;
}

LevelEvents::LevelEvent LevelEvents::event(const std::string &name) const {
    const auto& it = events_.find(name);

    if(it == events_.end())
        return 0;

    return it->second;
}
