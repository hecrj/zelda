#include <getopt.h>
#include "menu.hpp"
#include "../drawable.hpp"
#include "../font.hpp"

Menu::Menu(float x, float y, float separation) :
        x_(x),
        y_(y),
        separation_(separation)
{}

void Menu::Tick(double delta) {
    drawable_->Update(delta);
}

void Menu::Render() const {
    drawable_->Draw();

    for(const MenuOption& option : options_)
        Font::Render(option.position.x, option.position.y, option.text.c_str());
}

void Menu::AddOption(std::string const& text, std::function<void()> const callback) {
    MenuOption option;
    option.text = text;
    option.position.x = x_ - text.size() * (Font::WIDTH / 2);
    option.position.y = y_ + options_.size() * (Font::HEIGHT + separation_);
    option.callback = callback;

    options_.push_back(option);
}

bool Menu::IsFinished() const {
    return false;
}
