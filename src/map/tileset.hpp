#include <tsx_tileset.hpp>
#include <GL/gl.h>
#include "../graphic/sprite.hpp"

#pragma once

class Tileset {
public:
    Tileset(TSX::Tileset* tileset);

    Sprite* sprite(int tile_id);

    void RenderTiles(int width, int height, const std::vector<std::vector<int>>& tiles,
            int screen_width, int screen_height) const;

private:
    TSX::Tileset* info_;
    GLuint texture_;
    std::map<int, Sprite*> sprites_;
};
