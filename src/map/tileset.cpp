#include <SOIL.h>
#include <iostream>
#include <sstream>
#include "tileset.hpp"

Tileset::Tileset(TSX::Tileset *tileset) :
        info_(tileset),
        frames(tileset->frames),
        interval(tileset->interval),
        random(tileset->random)
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

    glBindTexture(GL_TEXTURE_2D, texture_);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Tileset::RenderTiles(int width, int height, const std::vector<std::vector<int>>& tiles, int frame) const {
    const TSX::Tileset& tileset = *info_;

    glBindTexture(GL_TEXTURE_2D, texture_);
    glBegin(GL_QUADS);

    for(int i = 0; i < height; ++i) {
        for(int j = 0; j < width; ++j) {
            int tile_id = tiles[i][j] - 1;

			if (tile_id < 0)
				continue;

            std::map<int, TSX::Tile>::const_iterator& tile = tileset.tiles.find(tile_id);

			if (tile != tileset.tiles.end())
				tile_id += tile->second.animated ? (tile->second.first_frame + frame) % tileset.frames : 0;

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
    tile_id--;

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

Tileset::~Tileset() {
    for(const auto& ksprite : sprites_)
        delete ksprite.second;

    glDeleteTextures(1, &texture_);
}

void Tileset::RenderIndividualTiles(float x, float y, const std::vector<std::vector<int>>& tiles) const {
    const TSX::Tileset& tileset = *info_;

    glBindTexture(GL_TEXTURE_2D, texture_);
    glBegin(GL_QUADS);

    for(int i = 0; i < tiles.size(); ++i) {
        for(int j = 0; j < tiles[0].size(); ++j) {
            int tile_id = tiles[i][j] - 1;

            int col = tile_id % tileset.width;
            int row = tile_id / tileset.width;

            if(tile_id != -1) {
                glTexCoord2f(
                        tileset.horizontal_ratio * col,
                        tileset.vertical_ratio * row
                );
                glVertex2d(x + float(j * tileset.tile_width), y + float(i * tileset.tile_height));

                glTexCoord2f(
                        tileset.horizontal_ratio * (col + 1),
                        tileset.vertical_ratio * row
                );
                glVertex2f(x + float((j + 1) * tileset.tile_width), y + float(i * tileset.tile_height));

                glTexCoord2f(
                        tileset.horizontal_ratio * (col + 1),
                        tileset.vertical_ratio * (row + 1)
                );
                glVertex2f(x + float((j + 1) * tileset.tile_width), y + float((i + 1) * tileset.tile_height));

                glTexCoord2f(
                        tileset.horizontal_ratio * col,
                        tileset.vertical_ratio * (row + 1)
                );
                glVertex2f(x + float(j * tileset.tile_width), y + float((i + 1) * tileset.tile_height));
            }
        }
    }

    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
}
