#pragma once

#include <array>
#include "vec2.hpp"

class Dir {
public:
    static const Dir DOWN;
    static const Dir UP;
    static const Dir RIGHT;
    static const Dir LEFT;
    static const Dir* ALL[];
    static const std::array<vec2i, 8> VECTORS;

    static const Dir& fromVector(const vec2f& vector);
    static const Dir& random();

    const vec2f& vector() const;
    int index() const;

private:
    vec2f vector_;
    unsigned int index_;
    Dir(const vec2f& vector, unsigned int index);
};
