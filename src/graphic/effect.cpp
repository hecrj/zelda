#include "effect.hpp"
#include "../entity.hpp"
#include "drawable.hpp"

Effect::Effect(Drawable* drawable) :
        Effect(drawable, 0)
{}

Effect::Effect(Drawable* drawable, Effect* next) :
        drawable_(drawable),
        next_(next)
{}

void Effect::Leave() {
    // Do nothing
}

Effect* Effect::next() const {
    return next_;
}
