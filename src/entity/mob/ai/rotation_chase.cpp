#include "rotation_chase.hpp"
#include "../moldorm.hpp"

RotationChase::RotationChase(Mob* mob) :
        super(mob)
{}

void RotationChase::Update(double delta) {
    Moldorm* moldorm = (Moldorm*) mob_;
    Entity* player = mob_->SeekPlayer();

    if(player) {
        vec2f dir_player = player->center() - moldorm->center();
        dir_player.normalize();
        vec2f dir = moldorm->direction();



        if(not(dir_player.x - 0.1 <= dir.x and dir.x <= dir_player.x + 0.1 and
                dir_player.y - 0.1 <= dir.y and dir.y <= dir_player.y + 0.1))
            moldorm->Rotate();
    }
}
