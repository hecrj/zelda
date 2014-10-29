#include "drawable.hpp"

Drawable::Drawable() :
    current_effect_(0)
{}

Drawable::~Drawable() {
    if(current_effect_)
        delete current_effect_;
}

void Drawable::Render() const {
    if(current_effect_)
        current_effect_->Render();
    else
        Draw();
}

void Drawable::Update(double delta) {
    if(current_effect_) {
        if(current_effect_->IsFinished()) {
            delete current_effect_;
            current_effect_ = 0;
        } else {
            current_effect_->Update(delta);
        }
    }
}

void Drawable::ChangeEffect(Effect* effect) {
    if(current_effect_)
        delete current_effect_;

    current_effect_ = effect;
}
