#include <GL/gl.h>
#include "bounce.hpp"
#include "../../entity.hpp"

const float Bounce::GRAVITY = 500;

Bounce::Bounce(Entity* entity, float height, float t) :
        super(entity),
        position_(vec2f(0, 0))
{
    speed_ = (-height - 0.5f * GRAVITY * t * t) / t;
    final_speed_ = -speed_;
}

void Bounce::Update(double delta) {
    position_ += vec2f(0, speed_  * (float)delta);
    speed_ += GRAVITY * delta;
}

void Bounce::Render() const {
    glPushMatrix();
    glTranslatef(0, position_.y, 0);
    entity_->Draw();
    glPopMatrix();
}

bool Bounce::IsFinished() const {
    return speed_ >= final_speed_;
}
