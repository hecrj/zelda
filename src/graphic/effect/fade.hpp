#pragma once

#include "../callback_effect.hpp"

class Fade : public CallbackEffect {
public:
    typedef CallbackEffect super;
    Fade(const std::string& type, Drawable* drawable, float duration, const std::function<void()>& callback);

    bool IsFinished() const;

    void Tick(double delta);
    void Render() const;

private:
    bool fade_in_;
    float duration_;
    float time_;
};