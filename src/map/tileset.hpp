#include <tsx_tileset.hpp>
#include <GL/gl.h>

#pragma once

class Tileset {
public:
    Tileset(TSX::Tileset* tileset);

    GLuint bind() const;

    void RenderTile(float x, float y, int tile_id) const;
    void RenderTiles(int width, int height, const std::vector<std::vector<int>>& tiles) const;

private:
    TSX::Tileset* info_;
    GLuint texture_;
};
