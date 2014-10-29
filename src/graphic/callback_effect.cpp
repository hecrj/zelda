#include <functional>
#include "callback_effect.hpp"

CallbackEffect::CallbackEffect(Drawable* drawable, const std::function<void()>& callback) :
        super(drawable),
        callback_(callback)
{}

void CallbackEffect::Leave() {
    callback_();
}
