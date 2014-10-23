#include <iostream>
#include <sstream>
#include "tile_map.hpp"
#include "SOIL.h"
#include "../debug.hpp"

TileMap::TileMap(const char* name)
{
    std::stringstream path;
    path << "res/level/" << name << ".tmx";
    map_ = TMX::parse(path.str().c_str());
    static_collidables_ = new Quadtree(0, Rectangle(0, 0, map_->width_pixels, map_->height_pixels));
    tileset_ = new Tileset(map_->tilesets[0]);

    InitBlockedTiles();
}

void TileMap::InitBlockedTiles() {
    TSX::Tileset* tileset = map_->tilesets[0];

    // Avoid adding the same rectangle twice
    std::vector<std::vector<bool>> blocked(map_->height, std::vector<bool>(map_->width, false));

    for(const auto& layer : map_->tile_layers_below) {
        // Populate blocked tiles
        for(int i = 0; i < layer->height; ++i) {
            for(int j = 0; j < layer->width; ++j) {
                if(blocked[i][j])
                    continue;

                int tile_id = layer->tiles[i][j] - 1;

                if(tileset->tiles[tile_id].Property("blocked") == "true") {
                    blocked_tiles_.push_back(new Rectangle(j*map_->tile_width, i*map_->tile_height,
                            map_->tile_width, map_->tile_height));
                    blocked[i][j] = true;
                }
            }
        }
    }

    for(Rectangle* blocked_tile : blocked_tiles_) {
        static_collidables_->Insert(blocked_tile);
    }
}

TileMap::~TileMap()
{
}

void TileMap::CollidablesFor(Rectangle* rectangle, std::vector<Rectangle*>& collidables) const {
    static_collidables_->Retrieve(rectangle, collidables);
}

bool TileMap::IsInbounds(Rectangle* rectangle) const {
    return IsInbounds(rectangle->position(), rectangle->width(), rectangle->height());
}

bool TileMap::IsInbounds(const vec2f& position, float width, float height) const {
    return position.x >= 0.0f and position.x + width < (float)map_->width_pixels and
            position.y >= 0.0f and position.y + height < (float)map_->height_pixels;
}

void TileMap::RenderLayers(const std::vector<TMX::TileLayer*>& layers) const
{
    // Only one tileset supported
    const Tileset& tileset = *tileset_;
    tileset_->bind();

    for(TMX::TileLayer* layer : layers)
        tileset.RenderTiles(layer->width, layer->height, layer->tiles);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void TileMap::RenderLayersBelow() const {
    RenderLayers(map_->tile_layers_below);
}

void TileMap::RenderLayersAbove() const {
    RenderLayers(map_->tile_layers_above);

    if(Debug::enabled) {
        for(Rectangle* r : blocked_tiles_)
            r->Render(0, 1, 0);

        static_collidables_->Render(0, 0, 1);
    }
}

void TileMap::Render() const {
    RenderLayersBelow();
    RenderLayersAbove();
}
