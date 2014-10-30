#pragma once

#include "tmx_map.hpp"
#include "GL/glut.h"
#include "../math/quadtree.hpp"
#include "tileset.hpp"

class TileMap
{
public:
	TileMap(const char* s);
	virtual ~TileMap();

    bool IsInbounds(Rectangle* rectangle) const;
    bool IsInbounds(const vec2f& position, float width, float height) const;

    virtual void CollidablesFor(Rectangle* rectangle, std::vector<Rectangle*>& collidables) const;

    void RenderLayersBelow(int frame) const;
    void RenderLayersAbove() const;

protected:
    TMX::Map* map_;
    Quadtree* static_collidables_;
    Tileset* tileset_;
    std::vector<GLuint> textures_below_;
    GLuint texture_above_;

private:
    std::vector<Rectangle*> blocked_tiles_;

    void InitBlockedTiles(const std::vector<TMX::TileLayer*>& layers, std::vector<std::vector<bool>>& blocked);
    void InitTextures();
    void RenderLayers(const std::vector<TMX::TileLayer*>& layers, int frame) const;
    void RenderTexture(GLuint texture) const;
    GLuint GenerateTexture(const std::vector<TMX::TileLayer*>& layers, int frame) const;
};
