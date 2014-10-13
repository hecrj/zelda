#pragma once

#include "vec2.hpp"

class Dir {
public:
    static const Dir DOWN;
    static const Dir UP;
    static const Dir RIGHT;
    static const Dir LEFT;
    static const Dir* ALL[];

    static const Dir& fromVector(const vec2f& vector);
    static const Dir& random();

    const vec2f& vector() const;

private:
    vec2f vector_;
    unsigned int index_;
    Dir(const vec2f& vector, unsigned int index);
};
