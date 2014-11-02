#include "level_screen.hpp"
#include "../entity/mob/ai/player.hpp"
#include "../audio/music.hpp"
#include "../graphic/effect/fade.hpp"
#include <iostream>
#include "../entity/mob/moldorm.hpp"

LevelScreen::LevelScreen(bool* keys, const char* name)
{
    Link* link = new Link();
    hud = new Hud(link);

    link->set_AI(new Player(link, keys));

    level = new Level(name, hud);
    level->AddPlayer(link, "start");

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
        std::cout << "Checkpoint level-screen.1" << std::endl;

        level->ChangeEffect(new Fade(Fade::OUT, 0.5, [this, map, place]{
            std::cout << "Checkpoint level-screen.1.1" << std::endl;

            std::vector<Entity*> players(level->players());
            std::cout << "Checkpoint level-screen.1.1.1" << std::endl;


            Level* old_level = level;
            level = new Level(map.c_str(), hud);
            std::cout << "Checkpoint level-screen.1.2" << std::endl;


            for(Entity* player : players){
                std::cout << "Checkpoint level-screen.2" << std::endl;

                level->AddPlayer(player, place);
            }

            std::cout << "Checkpoint level-screen.3" << std::endl;

            level->ChangeEffect(new Fade(Fade::IN, 0.5, [this, old_level]{
                delete old_level;
                level->Init();
            }));
            std::cout << "Checkpoint level-screen.4" << std::endl;

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
