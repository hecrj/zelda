#pragma once

#include "../screen.hpp"
#include "../graphic/drawable.hpp"
#include <string>

class OverScreen : public Screen {
public:
    typedef Screen super;

    OverScreen(const std::string& level_name);
    ~OverScreen();

    void Init();
    void Tick(double delta);
    void Render() const;

private:
    Drawable* over_;
};
