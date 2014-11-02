#include "dungeon_boss.hpp"
#include "../../audio/music.hpp"

namespace DungeonBossPrivate {
    void start(Level* level) {
        Music::ClearQueue();
        Music::FadeOut(0);
        Music::Enqueue("boss_intro", Music::NO_LOOP);
        Music::Enqueue("boss", Music::LOOP);
    }
};

DungeonBoss::DungeonBoss() {
    Register("start", DungeonBossPrivate::start);
}
