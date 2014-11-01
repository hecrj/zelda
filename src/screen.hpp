#pragma once

#include "screen.hpp"

class Screen {
public:
    Screen();

    virtual void Init();
    virtual void Tick(double delta) = 0;
    virtual void Render() const = 0;
};
