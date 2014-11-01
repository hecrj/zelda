#pragma once

#include "../screen.hpp"
#include "../graphic/spritesheet.hpp"
#include "../graphic/drawable.hpp"

class TitleScreen : public Screen {
public:
    typedef Screen super;

    static void Load();

    TitleScreen();
    ~TitleScreen();

    void Init();
    void Tick(double delta);
    void Render() const;

private:
    Drawable* title_;
};
