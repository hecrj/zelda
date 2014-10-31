#include <functional>
#include "callback_effect.hpp"

CallbackEffect::CallbackEffect(const std::function<void()>& callback) :
        callback_(callback)
{}

void CallbackEffect::Leave() {
    callback_();
}
