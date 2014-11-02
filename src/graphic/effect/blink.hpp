#include "timer.hpp"

class Blink : public Timer {
public:
    typedef Timer super;

    Blink(float duration, float interval, const CallbackEffect::Callback& callback);

    void Tick(double delta);
    void Render() const;

private:
    float interval_;
    float current_;
    bool show_;
};
