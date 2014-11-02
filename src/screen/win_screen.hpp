#pragma once

#include "../screen.hpp"
#include "../graphic/drawable.hpp"
#include <string>

class WinScreen : public Screen {
public:
    typedef Screen super;

    WinScreen();
    ~WinScreen();

    void Init();
    void Tick(double delta);
    void Render() const;

private:
    Drawable* win_;
};
