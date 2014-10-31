#include "drawable.hpp"

Drawable::Drawable() :
    current_effect_(0)
{}

Drawable::~Drawable() {
    if(current_effect_)
        delete current_effect_;
}

bool Drawable::IsHitbox() const {
    return false;
}

bool Drawable::IsEntity() const {
    return false;
}

void Drawable::Render() const {
    if(not current_effect_)
        Draw();
    else
        current_effect_->Render();
}

void Drawable::Tick(double delta) {
    if(not current_effect_) {
        Update(delta);
    } else {
        if(current_effect_->IsFinished()) {
            ChangeEffect(current_effect_->next());
        } else {
            current_effect_->Tick(delta);
        }
    }
}

void Drawable::ChangeEffect(Effect* effect) {
    Effect* old = current_effect_;
    current_effect_ = effect;

    if(current_effect_)
        current_effect_->set_drawable(this);

    if(old) {
        old->Leave();
        delete old;
    }
}
