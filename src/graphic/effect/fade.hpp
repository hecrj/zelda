#pragma once

#include "../callback_effect.hpp"

class Fade : public CallbackEffect {
public:
    typedef CallbackEffect super;

    static const bool IN;
    static const bool OUT;

    Fade(bool fade_in, float duration, const std::function<void()>& callback);

    bool IsFinished() const;

    void Tick(double delta);
    void Render() const;

private:
    bool fade_in_;
    float duration_;
    float time_;
};