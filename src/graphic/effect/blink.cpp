#include "blink.hpp"
#include "../drawable.hpp"

Blink::Blink(float duration, float interval, const CallbackEffect::Callback& callback) :
        super(duration, callback),
        interval_(interval),
        current_(0),
        show_(false)
{}


void Blink::Render() const {
    if(show_)
        drawable_->Draw();
}

void Blink::Tick(double delta) {
    super::Tick(delta);
    drawable_->Update(delta);

    if(current_ >= interval_) {
        current_ = 0;
        show_ = !show_;
    }

    current_ += delta;
}
