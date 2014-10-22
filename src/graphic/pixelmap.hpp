#pragma once

#include <vector>

struct Pixelmap {
    std::vector<std::vector<bool>> map_;

    Pixelmap(int width, int height);

    void Print() const;
};
