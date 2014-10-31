#pragma once

#include "../entity.hpp"
#include "../map/tileset.hpp"

class Door : public Entity {
public:
    typedef Entity super;

    static sf::SoundBuffer* OPEN_SOUND;
    static sf::SoundBuffer* UNLOCK_SOUND;
    static void Load();

    Door(float x, float y, int tile_id, Tileset* tileset);

    bool IsVulnerable() const;
    Sprite* CurrentSprite(vec2f& sprite_position) const;
    Sprite* CurrentSprite() const;

    void Draw() const;
    void Open();

private:
    bool opened_;
    std::vector<std::vector<int>> tiles_;
    Effect* open_effect_;
    Tileset* tileset_;
};
