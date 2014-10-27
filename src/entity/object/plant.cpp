#include "plant.hpp"

Plant::Plant(Sprite* sprite, float x, float y) :
        super(sprite, x, y)
{
    health_ = 1;
    type_ = PLANT;
}
