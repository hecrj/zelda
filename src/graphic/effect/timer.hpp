#pragma once

#include "../callback_effect.hpp"

class Timer : public CallbackEffect {
public:
    typedef CallbackEffect super;
    Timer(float duration, const std::function<void()>& callback);

    bool IsFinished() const;

    void Tick(double delta);
    void Render() const;

protected:
    float duration_;
    float elapsed_time_;
};
