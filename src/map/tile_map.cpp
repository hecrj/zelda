#include <GL/glew.h>
#include <iostream>
#include <sstream>
#include <GL/glut.h>
#include "tile_map.hpp"
#include "../debug.hpp"
#include "../game.hpp"

TileMap::TileMap(const char* name)
{
    std::stringstream path;
    path << "res/level/" << name << ".tmx";
    map_ = TMX::parse(path.str().c_str());
    static_collidables_ = new Quadtree(0, RectangleShape(0, 0, map_->width_pixels, map_->height_pixels));
    tileset_ = new Tileset(map_->tilesets[0]);

    // Avoid adding the same rectangle twice
    std::vector<std::vector<bool>> blocked(map_->height, std::vector<bool>(map_->width, false));
    InitBlockedTiles(map_->tile_layers_below, blocked);
    InitBlockedTiles(map_->tile_layers_above, blocked);

    InitTextures();
}

void TileMap::InitBlockedTiles(const std::vector<TMX::TileLayer*>& layers, std::vector<std::vector<bool>>& blocked) {
    TSX::Tileset* tileset = map_->tilesets[0];

    for(const auto& layer : layers) {
        // Populate blocked tiles
        for(int i = 0; i < layer->height; ++i) {
            for(int j = 0; j < layer->width; ++j) {
                if(blocked[i][j])
                    continue;

                int tile_id = layer->tiles[i][j] - 1;

				if (tile_id < 0 || tileset->tiles.find(tile_id) == tileset->tiles.end())
					continue;

				std::cout << tileset->tiles[tile_id].animated << std::endl;

                if(tileset->tiles[tile_id].Property("blocked") == "true") {
                    RectangleShape* blocked_tile = new RectangleShape(j*map_->tile_width, i*map_->tile_height,
                            map_->tile_width, map_->tile_height);

                    blocked_tiles_.push_back(blocked_tile);
                    static_collidables_->Insert(blocked_tile);
                    blocked[i][j] = true;
                }
            }
        }
    }
}

TileMap::~TileMap()
{
    delete map_;
    delete static_collidables_;
    delete tileset_;

    for(RectangleShape* tile : blocked_tiles_)
        delete tile;

    for(GLuint texture : textures_below_)
        glDeleteTextures(1, &texture);

    glDeleteTextures(1, &texture_above_);
}

void TileMap::CollidablesFor(RectangleShape* rectangle, std::vector<RectangleShape*>& collidables) const {
    static_collidables_->Retrieve(rectangle, collidables);
}

bool TileMap::IsInbounds(RectangleShape* rectangle) const {
    return IsInbounds(rectangle->position(), rectangle->width(), rectangle->height());
}

bool TileMap::IsInbounds(const vec2f& position, float width, float height) const {
    return position.x >= 0.0f && position.x + width < (float)map_->width_pixels &&
            position.y >= 0.0f && position.y + height < (float)map_->height_pixels;
}

void TileMap::RenderLayers(const std::vector<TMX::TileLayer*>& layers, int frame) const
{
    for(TMX::TileLayer* layer : layers)
        tileset_->RenderTiles(layer->width, layer->height, layer->tiles, frame);
}

void TileMap::RenderLayersBelow(int frame) const {
    RenderTexture(textures_below_[frame]);
}

void TileMap::RenderLayersAbove() const {
    RenderTexture(texture_above_);

    if(Debug::enabled) {
        for(RectangleShape* r : blocked_tiles_)
            r->DrawBox(0, 1, 0);

        static_collidables_->Render(0, 0, 1);
    }
}

void TileMap::InitTextures() {
    // Prepare the viewport to render the map texture
    glViewport(0, 0, map_->width_pixels, map_->height_pixels);

    // Prepare the projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, map_->width_pixels, map_->height_pixels, 0, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Create and bind framebuffer
    GLuint fb = 0;
    glGenFramebuffers(1, &fb);
    glBindFramebuffer(GL_FRAMEBUFFER, fb);

    // Generate the texture below entities
    for(int i = 0; i < tileset_->frames; ++i)
        textures_below_.push_back(GenerateTexture(map_->tile_layers_below, i));

    // Generate the texture above entities
    glGenTextures(1, &texture_above_);
    glBindTexture(GL_TEXTURE_2D, texture_above_);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, map_->width_pixels, map_->height_pixels, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_above_, 0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    RenderLayers(map_->tile_layers_above, 0);

    // Unbind and delete framebuffer
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDeleteFramebuffers(1, &fb);

    glViewport(0, 0, Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT, 0, 0, 1);
    glMatrixMode(GL_MODELVIEW);
}

void TileMap::RenderTexture(GLuint texture) const {
    glBindTexture(GL_TEXTURE_2D, texture);
    glBegin(GL_QUADS);

    glTexCoord2f(0, 1);
    glVertex2f(0, 0);

    glTexCoord2f(1, 1);
    glVertex2f(map_->width_pixels, 0);

    glTexCoord2f(1, 0);
    glVertex2f(map_->width_pixels, map_->height_pixels);

    glTexCoord2f(0, 0);
    glVertex2f(0, map_->height_pixels);

    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint TileMap::GenerateTexture(const std::vector<TMX::TileLayer*>& layers, int frame) const {
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, map_->width_pixels, map_->height_pixels, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    RenderLayers(layers, frame);

	glBindTexture(GL_TEXTURE_2D, 0);

    return texture;
}
