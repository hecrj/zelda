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

    void RenderLayers(const std::vector<TMX::TileLayer*>& layers) const;
    void RenderLayersBelow() const;
    void RenderLayersAbove() const;
	virtual void Render() const;

protected:
    TMX::Map* map_;
    Quadtree* static_collidables_;
    Tileset* tileset_;

private:
    std::vector<Rectangle*> blocked_tiles_;

    void InitBlockedTiles();
};
