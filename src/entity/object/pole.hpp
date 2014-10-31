#pragma once

#include "../../entity.hpp"

class Pole : public Entity {
public:
    typedef Entity super;

    enum Type { BLUE, YELLOW };
    enum Status { BLUE_OPEN, BLUE_CLOSED, TRANSITION };

    static Type OPEN;

    Pole(float x, float y, Type type, Sprite* closed, Sprite* transition);

    bool CanCollideWith(Rectangle* rectangle) const;

    void Draw() const;

private:
    static Status INTERNAL_STATUS;

    Type type_;
    Sprite* closed_;
    Sprite* transition_;
};
