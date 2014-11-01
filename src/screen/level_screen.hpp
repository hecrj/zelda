#pragma once

#include "../map/level.hpp"
#include "../hud.hpp"
#include "../screen.hpp"

class LevelScreen : public Screen {
public:
    typedef Screen super;
    LevelScreen(bool* keys, const char* name);
    ~LevelScreen();

    void Tick(double delta);
    void Render() const;

private:
    Level* level;
    Hud* hud;
};
