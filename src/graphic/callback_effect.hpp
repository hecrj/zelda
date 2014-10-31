#pragma once

#include <functional>
#include "effect.hpp"

class CallbackEffect : public Effect {
public:
    typedef Effect super;
    CallbackEffect(const std::function<void()>& callback);

    void Leave();

protected:
    std::function<void()> callback_;
};
