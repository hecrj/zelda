#ifdef _WIN32
#include <Windows.h>
#endif
#include <iostream>
#include "title_screen.hpp"
#include "../audio/music.hpp"
#include "../utils.hpp"
#include "../game.hpp"
#include "../graphic/effect/fade.hpp"
#include "../graphic/effect/timer.hpp"
#include "../debug.hpp"
#include "../graphic/effect/menu.hpp"

namespace TitleScreenPrivate {
    SpriteSheet* STARS;
    SpriteSet* STAR1;
    SpriteSet* STAR2;
    GLuint BACKGROUND;
    GLuint LOGO;
    typedef void (*Drawer)();
    float width = 1;
    float height = 1;
    float logo_x = 1;
    float logo_y = 1;
    float logo_width = 183.f;
    float logo_height = 99.f;

    void CalculateCoords() {
        width = Game::WIDTH;
        height = Game::HEIGHT;

        if(Game::WIDTH > Game::HEIGHT) {
            height = 144 * (float) Game::WIDTH / 256;
        } else {
            width *= 256 * (float) Game::HEIGHT / 144;
        }

        if(height > Game::HEIGHT) {
            width *= Game::HEIGHT / height;
            height = Game::HEIGHT;
        }

        logo_x = (width - logo_width) / 2.0f;
        logo_y = (height - logo_height) / 2.0f - 60;
    }

    void DrawBackground() {
        CalculateCoords();

        glScalef(Game::SCALE, Game::SCALE, 0);
        glTranslatef((Game::WIDTH - width) / 2.0f, (Game::HEIGHT - height) / 2.0f, 0);

        glBindTexture(GL_TEXTURE_2D, BACKGROUND);
        glBegin(GL_QUADS);

        glTexCoord2f(0, 0);
        glVertex2f(0, 0);

        glTexCoord2f(1, 0);
        glVertex2f(width, 0);

        glTexCoord2f(1, 1);
        glVertex2f(width, height);

        glTexCoord2f(0, 1);
        glVertex2f(0, height);

        glEnd();
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void DrawLogo() {
        glBindTexture(GL_TEXTURE_2D, LOGO);
        glBegin(GL_QUADS);

        glTexCoord2f(0, 0);
        glVertex2f(logo_x, logo_y);

        glTexCoord2f(1, 0);
        glVertex2f(logo_x + logo_width, logo_y);

        glTexCoord2f(1, 1);
        glVertex2f(logo_x + logo_width, logo_y + logo_height);

        glTexCoord2f(0, 1);
        glVertex2f(logo_x, logo_y + logo_height);

        glEnd();
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    class FadeTransparent : public Timer {
    private:
        Drawer drawer_;

    public:
        FadeTransparent(Drawer drawer, float duration, const Callback& callback, Effect* next) :
                Timer(duration, callback, next),
                drawer_(drawer)
        {};

        void Tick(double delta) {
            Timer::Tick(delta);
            drawable_->Update(delta);
        }

        void Render() const {
            drawable_->Draw();
            glColor4f(1, 1, 1, elapsed_time_ * (1.0f / duration_));
            drawer_();
            glColor4f(1, 1, 1, 1);
        }
    };

    class Title : public Drawable {
    private:
        float accum_;
        std::vector<Drawer> drawers_;

        struct Star {
            Animation* animation;
            vec2f position;
        };

        std::list<Star> stars_;

        void AddStar() {
            Star star;
            star.position = vec2f(logo_x + rand() % (int)logo_width, logo_y + rand() % (int)logo_height);
            star.animation = new Animation(rand() % 2 == 0 ? STAR1 : STAR2);
            stars_.push_back(star);
        }

    public:
        Title()
        {
            accum_ = 0;
        }

        ~Title() {
            for(Star& star : stars_)
                delete star.animation;
        }

        void Init() {
            CalculateCoords();
            Menu* menu = new Menu(width / 2.0f, 60.0f + height / 2.0f, 10);

            menu->AddOption("New Game", [this]{
                Music::ClearQueue();
                Music::FadeOut(2);
                ChangeEffect(new Fade(Fade::FADE_OUT, 2, []{
                    Game::INSTANCE.LoadLevel("intro");
                }));
            });

            menu->AddOption("Exit", []{
                Game::INSTANCE.Exit();
            });

            ChangeEffect(
                    // Wait a second for the music to start
                    new Timer(1, []{
                    },
                    new FadeTransparent(DrawBackground, 4.2f, [this]{
                        drawers_.push_back(DrawBackground);
                    }, new FadeTransparent(DrawLogo, 1.9, [this]{
                        drawers_.push_back(DrawLogo);
                    }, menu)
            )));
        }

        void Update(double delta) {
            accum_ += delta;

            if(drawers_.size() > 0) {
                auto it = stars_.begin();
                while(it != stars_.end()) {
                    Star& star = *it;

                    if(! star.animation->IsFinished()) {
                        star.animation->Update(delta);
                        ++it;
                    } else {
                        delete star.animation;
                        it = stars_.erase(it);
                    }
                }

                if(accum_ >= 0.1f) {
                    // Background drawn
                    if(Debug::enabled)
                        std::cout << "Number of stars: " << stars_.size() << std::endl;

                    if(rand() % 100 <= 50)
                        AddStar();

                    accum_ = 0;
                }
            }
        }

        void Draw() const {
            for(Drawer drawer : drawers_)
                drawer();

            if(drawers_.size() > 0) {
                for(const Star& star : stars_)
                    star.animation->Render(star.position);
            }
        }
    };
};

TitleScreen::TitleScreen()
{
    title_ = new TitleScreenPrivate::Title();
}

TitleScreen::~TitleScreen() {
    delete title_;
}

void TitleScreen::Load() {
    TitleScreenPrivate::STARS = new SpriteSheet("title/stars.png", 64, 32, 16, 16);
    TitleScreenPrivate::STAR1 = new SpriteSet(TitleScreenPrivate::STARS->GetSprites(0, 4), 0, 30, vec2f(0,0));
    TitleScreenPrivate::STAR2 = new SpriteSet(TitleScreenPrivate::STARS->GetSprites(1, 4), 0, 30, vec2f(0, 0));
    TitleScreenPrivate::BACKGROUND = LoadTexture("title/background.png");
    TitleScreenPrivate::LOGO = LoadTexture("title/logo.png");
}

void TitleScreen::Tick(double delta) {
    title_->Tick(delta);
}

void TitleScreen::Render() const {
    title_->Render();
}

void TitleScreen::Init() {
    Music::Enqueue("crystal_intro", Music::NO_LOOP);
    Music::Enqueue("crystal", Music::LOOP);

    ((TitleScreenPrivate::Title*)title_)->Init();
}
