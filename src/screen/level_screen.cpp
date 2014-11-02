#include "level_screen.hpp"
#include "../entity/mob/ai/player.hpp"
#include "../audio/music.hpp"
#include "../graphic/effect/fade.hpp"
#include "../entity/mob/moldorm.hpp"

LevelScreen::LevelScreen(bool* keys, const char* name)
{
    Link* link = new Link();
    hud = new Hud(link);

    link->set_AI(new Player(link, keys));

    level = new Level(name, hud);
    level->AddPlayer(link, "start");

    Moldorm* moldorm = new Moldorm(160, 160);
    level->AddEntity(moldorm);

    level->ChangeEffect(new Fade(Fade::IN, 0.5, [this] {
        level->Init();
    }));
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
            level = new Level(map.c_str(), hud);

            for(Entity* player : players)
                level->AddPlayer(player, place);

            level->ChangeEffect(new Fade(Fade::IN, 0.5, [this, old_level]{
                delete old_level;
                level->Init();
            }));
        }));
    }
}

void LevelScreen::Render() const {
    level->Render();
}

LevelScreen::~LevelScreen() {
    delete level;
    delete hud;
}
