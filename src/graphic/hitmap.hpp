#pragma once

#include <vector>

struct Hitmap {
    std::vector<std::vector<bool>> map_;

    Hitmap(int width, int height);

    void Print() const;
};
