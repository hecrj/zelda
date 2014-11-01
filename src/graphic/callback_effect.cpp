#include <functional>
#include "callback_effect.hpp"

CallbackEffect::CallbackEffect(const std::function<void()>& callback) :
        callback_(callback)
{}

CallbackEffect::CallbackEffect(const std::function<void()>& callback, Effect* next) :
        super(next),
        callback_(callback)
{}

void CallbackEffect::Leave() {
    callback_();
}
