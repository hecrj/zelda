#ifdef _WIN32
#include <Windows.h>
#endif
#include "win_screen.hpp"
#include "../audio/music.hpp"
#include "../graphic/effect/fade.hpp"
#include "../graphic/font.hpp"
#include "../game.hpp"
#include "../graphic/effect/timer.hpp"

namespace WinScreenPrivate {
    const std::string THE_END = "THE END";

    class Win : public Drawable {
        float accum_;
        unsigned int until_;

    public:
        Win() :
                accum_(0),
                until_(0)
        {}

        void Update(double delta) {
            if(until_ > THE_END.size()) {
                until_ = (unsigned int) THE_END.size();
                ChangeEffect(new Timer(2, []{
                    Music::ClearQueue();
                    Music::FadeOut(2);
                }, new Fade(Fade::FADE_OUT, 2, []{
                    Game::INSTANCE.LoadTitleScreen();
                })));
            } else {
                accum_ += delta;
                until_ = (unsigned int) (accum_ * 2.f);
            }
        }

        void Draw() const {
            glScalef(Game::SCALE, Game::SCALE, 0);
            Font::Render((Game::WIDTH - THE_END.size() * Font::WIDTH) / 2, 50, THE_END.substr(0, until_).c_str());
        }
    };
};

WinScreen::WinScreen() {
    win_ = new WinScreenPrivate::Win();
}

WinScreen::~WinScreen() {
    delete win_;
}

void WinScreen::Init() {
    Music::Enqueue("ending", Music::LOOP);
}

void WinScreen::Tick(double delta) {
    win_->Tick(delta);
}

void WinScreen::Render() const {
    win_->Render();
}
