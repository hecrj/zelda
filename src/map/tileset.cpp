#include <SOIL.h>
#include <sstream>
#include "tileset.hpp"

Tileset::Tileset(TSX::Tileset *tileset) :
        info_(tileset)
{
    texture_ = SOIL_load_OGL_texture(info_->image.source.c_str(),
            SOIL_LOAD_RGBA,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_MULTIPLY_ALPHA);

    if(0 == texture_) {
        std::stringstream error;
        error << "SOIL loading error: " << SOIL_last_result();
        throw error.str();
    }
}

void Tileset::RenderTiles(int width, int height, const std::vector<std::vector<int>>& tiles) const {
    const TSX::Tileset& tileset = *info_;

    glBindTexture(GL_TEXTURE_2D, texture_);
    glBegin(GL_QUADS);

    for(int i = 0; i < height; ++i) {
        for(int j = 0; j < width; ++j) {
            int tile_id = tiles[i][j] - 1;
            int col = tile_id % tileset.width;
            int row = tile_id / tileset.width;

            if(tile_id != -1) {
                glTexCoord2f(
                        tileset.horizontal_ratio * col,
                        tileset.vertical_ratio * row
                );
                glVertex2d(float(j * tileset.tile_width), float(i * tileset.tile_height));

                glTexCoord2f(
                        tileset.horizontal_ratio * (col + 1),
                        tileset.vertical_ratio * row
                );
                glVertex2f(float((j + 1) * tileset.tile_width), float(i * tileset.tile_height));

                glTexCoord2f(
                        tileset.horizontal_ratio * (col + 1),
                        tileset.vertical_ratio * (row + 1)
                );
                glVertex2f(float((j + 1) * tileset.tile_width), float((i + 1) * tileset.tile_height));

                glTexCoord2f(
                        tileset.horizontal_ratio * col,
                        tileset.vertical_ratio * (row + 1)
                );
                glVertex2f(float(j * tileset.tile_width), float((i + 1) * tileset.tile_height));
            }
        }
    }

    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
}

Sprite* Tileset::sprite(int tile_id) {
    std::map<int, Sprite*>::iterator it = sprites_.find(tile_id);

    if(it != sprites_.end())
        return it->second;

    const TSX::Tileset& tileset = *info_;
    Sprite* sprite = new Sprite(texture_, tileset.tile_width, tileset.tile_height,
            tileset.horizontal_ratio * (tile_id % tileset.width),
            tileset.vertical_ratio * (tile_id / tileset.width),
            tileset.horizontal_ratio,
            tileset.vertical_ratio
    );

    sprites_[tile_id] = sprite;
    return sprite;
}
