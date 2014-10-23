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

GLuint Tileset::bind() const {
    glBindTexture(GL_TEXTURE_2D, texture_);
}

void Tileset::RenderTile(float x, float y, int tile_id) const {
    const TSX::Tileset& tileset = *info_;

    glBegin(GL_QUADS);

    glTexCoord2f(
            tileset.horizontal_ratio * (tile_id % tileset.width),
            tileset.vertical_ratio * (tile_id / tileset.width)
    );
    glVertex2d(x, y);

    glTexCoord2f(
            tileset.horizontal_ratio * ((tile_id % tileset.width) + 1),
            tileset.vertical_ratio * (tile_id / tileset.width)
    );
    glVertex2f(x + tileset.tile_width, y);

    glTexCoord2f(
            tileset.horizontal_ratio * ((tile_id % tileset.width) + 1),
            tileset.vertical_ratio * ((tile_id / tileset.width) + 1)
    );
    glVertex2f(x + tileset.tile_width, y + tileset.tile_height);

    glTexCoord2f(
            tileset.horizontal_ratio * (tile_id % tileset.width),
            tileset.vertical_ratio * ((tile_id / tileset.width) + 1)
    );
    glVertex2f(x, y + tileset.tile_height);

    glEnd();
}

void Tileset::RenderTiles(int width, int height, const std::vector<std::vector<int>>& tiles) const {
    const TSX::Tileset& tileset = *info_;

    for(int i = 0; i < height; ++i) {
        for(int j = 0; j < width; ++j) {
            int tile_id = tiles[i][j] - 1;

            if(tile_id != -1) {
                glBegin(GL_QUADS);

                glTexCoord2f(
                        tileset.horizontal_ratio * (tile_id % tileset.width),
                        tileset.vertical_ratio * (tile_id / tileset.width)
                );
                glVertex2d(float(j * tileset.tile_width), float(i * tileset.tile_height));

                glTexCoord2f(
                        tileset.horizontal_ratio * ((tile_id % tileset.width) + 1),
                        tileset.vertical_ratio * (tile_id / tileset.width)
                );
                glVertex2f(float((j + 1) * tileset.tile_width), float(i * tileset.tile_height));

                glTexCoord2f(
                        tileset.horizontal_ratio * ((tile_id % tileset.width) + 1),
                        tileset.vertical_ratio * ((tile_id / tileset.width) + 1)
                );
                glVertex2f(float((j + 1) * tileset.tile_width), float((i + 1) * tileset.tile_height));

                glTexCoord2f(
                        tileset.horizontal_ratio * (tile_id % tileset.width),
                        tileset.vertical_ratio * ((tile_id / tileset.width) + 1)
                );
                glVertex2f(float(j * tileset.tile_width), float((i + 1) * tileset.tile_height));

                glEnd();
            }
        }
    }
}
