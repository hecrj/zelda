#include "door.hpp"
#include "../audio/sound.hpp"
#include "../graphic/effect/overlay.hpp"

sf::SoundBuffer* Door::OPEN_SOUND;
sf::SoundBuffer* Door::UNLOCK_SOUND;

void Door::Load() {
    OPEN_SOUND = Sound::Buffer("door/open.wav");
    UNLOCK_SOUND = Sound::Buffer("door/unlock.wav");
}

Door::Door(float x, float y, int tile_id, Tileset* tileset) :
        super(x, y, 32, 24),
        tileset_(tileset),
        opened_(false)
{
    is_vulnerable_ = false;
    tiles_ = std::vector<std::vector<int>>(2, std::vector<int>(2));

    for(int i = 0; i < 2; ++i) {
        for(int j = 0; j < 2; ++j) {
            tiles_[i][j] = tile_id;
            tile_id++;
        }
    }

    std::vector<std::vector<int>> animation_overlay(2, std::vector<int>(2));
    for(int i = 0; i < 2; ++i) {
        for(int j = 0; j < 2; ++j) {
            animation_overlay[i][j] = tile_id;
            tile_id++;
        }
    }

    open_effect_ = new Overlay(0.1, position_.x, position_.y, tileset, animation_overlay, [this]{
        Kill();
    });
    die_sound_ = OPEN_SOUND;
}

void Door::Draw() const {
    if(IsAlive())
        tileset_->RenderIndividualTiles(position_.x, position_.y, tiles_);
}

void Door::Open() {
    if(not opened_) {
        Sound::Play(UNLOCK_SOUND);
        ChangeEffect(open_effect_);
        open_effect_ = 0;
        opened_ = true;
    }
}
