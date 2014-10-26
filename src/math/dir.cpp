#include <stdlib.h>
#include "dir.hpp"

Dir::Dir(const vec2f& vector, unsigned int index) :
        vector_(vector),
        index_(index)
{}

const Dir& Dir::fromVector(const vec2f& vector) {
    if(vector.x == 0)
        return vector.y > 0 ? Dir::DOWN : Dir::UP;

    return vector.x > 0 ? Dir::RIGHT : Dir::LEFT;
}

const Dir& Dir::random() {
    return *Dir::ALL[rand() % 4];
}

const vec2f& Dir::vector() const {
    return vector_;
}

int Dir::index() const {
    return index_;
}

const Dir Dir::DOWN = Dir(vec2f(0, 1), 0);
const Dir Dir::UP = Dir(vec2f(0, -1), 1);
const Dir Dir::RIGHT = Dir(vec2f(1, 0), 2);
const Dir Dir::LEFT = Dir(vec2f(-1, 0), 3);
const Dir* Dir::ALL[] = { &Dir::DOWN, &Dir::UP, &Dir::RIGHT, &Dir::LEFT };
const std::array<vec2i, 8> Dir::VECTORS = {
        vec2i(0, 1),
        vec2i(0, -1),
        vec2i(1, 0),
        vec2i(-1, 0),
        vec2i(-1, -1),
        vec2i(-1, 1),
        vec2i(1, -1),
        vec2i(1, 1)
};
