#ifdef _WIN32
#include <Windows.h>
#endif
#include <functional>
#include <GL/gl.h>
#include <iostream>
#include "fade.hpp"
#include "../drawable.hpp"
#include "../../game.hpp"

const bool Fade::FADE_IN = true;
const bool Fade::FADE_OUT = false;

Fade::Fade(bool fade_in, float duration, const std::function<void()>& callback) :
        super(callback),
        fade_in_(fade_in),
        duration_(duration),
        time_(0)
{}

bool Fade::IsFinished() const {
    return time_ >= duration_;
}

void Fade::Tick(double delta) {
    time_ += delta;

    if(time_ > duration_)
        time_ = duration_;
}

void Fade::Render() const {
    drawable_->Draw();

    float alpha = time_ / duration_;

    if(fade_in_)
        alpha = 1 - alpha;

    glColor4f(0, 0, 0, alpha);

    glPushMatrix();
    glLoadIdentity();
    glBegin(GL_QUADS);

    glVertex2f(0, 0);
    glVertex2f(Game::WINDOW_WIDTH, 0);
    glVertex2f(Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT);
    glVertex2f(0, Game::WINDOW_HEIGHT);

    glEnd();
    glPopMatrix();

    glColor4f(1, 1, 1, 1);
}
