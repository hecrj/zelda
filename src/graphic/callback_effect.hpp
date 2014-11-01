#pragma once

#include <functional>
#include "effect.hpp"

class CallbackEffect : public Effect {
public:
    typedef Effect super;
    typedef std::function<void()> Callback;

    CallbackEffect(const std::function<void()>& callback);
    CallbackEffect(const std::function<void()>& callback, Effect* next);

    void Leave();

protected:
    std::function<void()> callback_;
};
