#include "effect.hpp"
#include "../entity.hpp"
#include "drawable.hpp"

Effect::Effect() :
        Effect(0)
{}

Effect::Effect(Effect* next) :
        next_(next),
        drawable_(0)
{}

void Effect::Leave() {
    // Do nothing
}

Effect* Effect::next() const {
    return next_;
}

void Effect::set_drawable(Drawable* drawable) {
    drawable_ = drawable;
}
