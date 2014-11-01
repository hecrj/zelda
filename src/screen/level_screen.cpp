#include "level_screen.hpp"
#include "../entity/mob/ai/player.hpp"
#include "../audio/music.hpp"
#include "../graphic/effect/fade.hpp"

LevelScreen::LevelScreen(bool* keys, const char* name)
{
    // Load demo map
    level = new Level(name);

    Link* link = new Link();
    hud = new Hud(link);

    link->set_AI(new Player(link, keys));

    level->AddPlayer(link, "start");
}

void LevelScreen::Tick(double delta) {
    if(not level->transition_requested()) {
        level->Tick(delta);
    } else {
        Music::ClearQueue();
        Music::FadeOut(0.5);

        std::string map;
        std::string place;
        level->consume_transition(map, place);

        level->ChangeEffect(new Fade(Fade::OUT, 0.5, [this, map, place]{
            std::vector<Entity*> players(level->players());

            Level* old_level = level;
            level = new Level(map.c_str());

            for(Entity* player : players)
                level->AddPlayer(player, place);

            level->ChangeEffect(new Fade(Fade::IN, 0.5, [old_level]{
                delete old_level;
            }));
        }));
    }
}

void LevelScreen::Render() const {
    level->Render();
    hud->Render();
}

LevelScreen::~LevelScreen() {
    delete level;
    delete hud;
}
