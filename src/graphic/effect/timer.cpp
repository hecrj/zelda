#include "timer.hpp"
#include "../drawable.hpp"

Timer::Timer(float duration, const std::function<void()>& callback) :
        super(callback),
        duration_(duration)
{}

bool Timer::IsFinished() const {
    return elapsed_time_ >= duration_;
}

void Timer::Tick(double delta) {
    elapsed_time_ += delta;
}

void Timer::Render() const {
    drawable_->Draw();
}
