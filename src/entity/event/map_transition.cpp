#include <iostream>
#include "map_transition.hpp"
#include "../../game.hpp"
#include "../../audio/sound.hpp"
#include "../object/door.hpp"

MapTransition::MapTransition(Level* level, float x, float y, float width, float height,
        const std::string& name, const std::string& orientation, const std::string& map, const std::string& place) :
        super(level, x, y, width, height),
        map_(map),
        place_(place)
{
    if(map_.empty())
        Game::Error("Map not defined at map_transition:", name);

    if(place_.empty())
        Game::Error("Place not defined at map_transition:", name);

    level->AddLocation(new Location(x, y, width, height, name, orientation));
}

bool MapTransition::HandleCollisionWith(Mob* mob) {
    Sound::Play(Door::OPEN_SOUND);
    level_->Transition(map_, place_);

    return false;
}
