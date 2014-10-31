#pragma once

#include "../../entity.hpp"

class Pole : public Entity {
public:
    typedef Entity super;

    enum Type { BLUE, YELLOW };

    static Type OPEN;
    static bool IN_TRANSITION;

    Pole(float x, float y, Type type, Sprite* closed, Sprite* transition);

    bool CanCollideWith(Rectangle* rectangle) const;

    void Draw() const;

private:
    Type type_;
    Sprite* closed_;
    Sprite* transition_;
};
