#include "menu.hpp"
#include "../drawable.hpp"
#include "../font.hpp"
#include "../../game.hpp"
#include "../../audio/sound.hpp"

sf::SoundBuffer* Menu::MOVE_CURSOR_SOUND = Sound::Buffer("menu/move_cursor.wav");
sf::SoundBuffer* Menu::SELECT_SOUND = Sound::Buffer("menu/select.wav");

Menu::Menu(float x, float y, float separation) :
        x_(x),
        y_(y),
        separation_(separation),
        selected_(0)
{}

void Menu::Tick(double delta) {
    drawable_->Update(delta);

    if(Game::INSTANCE.ConsumeKey(GLUT_KEY_DOWN)) {
        selected_ = (selected_ + 1) % (int) options_.size();

        Sound::Play(MOVE_CURSOR_SOUND);
    } else if(Game::INSTANCE.ConsumeKey(GLUT_KEY_UP)) {
        selected_--;

        if(selected_ < 0)
            selected_ = (int)options_.size() - 1;

        Sound::Play(MOVE_CURSOR_SOUND);
    } else if(Game::INSTANCE.ConsumeKey(Game::ACTION_KEY)) {
        Sound::Play(SELECT_SOUND);
        options_[selected_].callback();
    }
}

void Menu::Render() const {
    drawable_->Draw();

    for(int i = 0; i < options_.size(); ++i) {
        const MenuOption& option = options_[i];

        Font::Render(option.position.x, option.position.y, option.text.c_str());

        if(i == selected_) {
            float x = option.position.x - 12;
            glBegin(GL_TRIANGLES);

            glVertex2f(x, option.position.y + 8);
            glVertex2f(x + 8, option.position.y + (Font::HEIGHT / 2));
            glVertex2f(x, option.position.y + Font::HEIGHT - 8);

            glEnd();
        }
    }
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
