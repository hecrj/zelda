#include "rotation_fade.hpp"
#include "../../entity.hpp"

const float RotationFade::ROTATION = 20;
const float RotationFade::REDUCTION = 0.05;


RotationFade::RotationFade() :
        rotation_(0.0f)
{
    size_=1.0f;
    final_size_=0.1f;
}

void RotationFade::Tick(double delta) {
    rotation_ += ROTATION;
    size_ -= REDUCTION;
}

void RotationFade::Render() const {
    float auxX = -((Entity*)this->drawable_)->position().x-((Entity*)this->drawable_)->width()/2;
    float auxY = -((Entity*)this->drawable_)->position().y-((Entity*)this->drawable_)->height()/2;
    glPushMatrix();
    glTranslatef(-auxX,-auxY,0);
    glRotatef(rotation_,0.0f,0.0f,1.0f);
    glScalef(size_,  size_,  1.0f);
    glTranslatef(auxX,auxY,0);
    drawable_->Draw();
    glPopMatrix();
}

bool RotationFade::IsFinished() const {
    return size_ <= final_size_;
}
