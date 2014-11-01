#include "over_screen.hpp"
#include "../audio/music.hpp"
#include "../graphic/effect/fade.hpp"
#include "../graphic/font.hpp"
#include "../game.hpp"
#include "../graphic/effect/menu.hpp"

namespace OverScreenPrivate {
    const std::string GAME_OVER = "GAME OVER";

    class Over : public Drawable {
        std::string level_name_;
        float accum_;
        unsigned int until_;
        bool menu_shown_;

    public:
        Over(const std::string& level_name) :
                level_name_(level_name),
                accum_(0),
                until_(0),
                menu_shown_(false)
        {}

        void Update(double delta) {
            if(until_ > GAME_OVER.size()) {
                until_ = (unsigned int) GAME_OVER.size();

                if(not menu_shown_) {
                    Menu* menu = new Menu(Game::WIDTH / 2, 225, 20);

                    menu->AddOption("Continue", [this]{
                        Music::ClearQueue();
                        Music::FadeOut(1);

                        ChangeEffect(new Fade(Fade::OUT, 1, [this] {
                            Game::INSTANCE.LoadLevel(level_name_.c_str());
                        }));
                    });

                    menu->AddOption("Return to title", [this] {
                        Music::ClearQueue();
                        Music::FadeOut(1);

                        ChangeEffect(new Fade(Fade::OUT, 1, [] {
                            Game::INSTANCE.LoadTitleScreen();
                        }));
                    });

                    ChangeEffect(menu);
                    menu_shown_ = true;
                }
            } else {
                accum_ += delta;
                until_ = (unsigned int) (accum_ * 2.f);
            }
        }

        void Draw() const {
            glScalef(Game::SCALE, Game::SCALE, 0);
            Font::Render((Game::WIDTH - GAME_OVER.size() * Font::WIDTH) / 2, 50, GAME_OVER.substr(0, until_).c_str());
        }
    };
};

OverScreen::OverScreen(const std::string& level_name) {
    over_ = new OverScreenPrivate::Over(level_name);
}

OverScreen::~OverScreen() {
    delete over_;
}

void OverScreen::Init() {
    Music::Enqueue("game_over", Music::LOOP);
}

void OverScreen::Tick(double delta) {
    over_->Tick(delta);
}

void OverScreen::Render() const {
    over_->Render();
}
