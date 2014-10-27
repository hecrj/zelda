#include "plant.hpp"
#include "../item/rupee.hpp"

Plant::Plant(Level* level, Sprite* sprite, float x, float y) :
        super(level, sprite, x, y)
{
    health_ = 1;
    type_ = PLANT;
}

void Plant::Dead() {
    if(rand() % 100 < 80)
        return;

    const vec2f& pos = center();
    level_->AddEntity(Rupee::Random(pos.x, pos.y));
}
