#include "overlay.hpp"
#include "../drawable.hpp"

Overlay::Overlay(float duration, float x, float y, Tileset* tileset, const std::vector<std::vector<int>>& tiles,
        const std::function<void()>& callback) :
        super(callback),
        duration_(duration),
        accum_(0),
        x_(x),
        y_(y),
        tileset_(tileset),
        tiles_(tiles)
{

}

void Overlay::Tick(double delta) {
    accum_ += delta;
}

bool Overlay::IsFinished() const {
    return accum_ >= duration_;
}

void Overlay::Render() const {
    drawable_->Draw();
    tileset_->RenderIndividualTiles(x_, y_, tiles_);
}
