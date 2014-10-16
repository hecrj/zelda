#pragma once

#include "tmx_map.hpp"
#include "GL/glut.h"
#include "../math/quadtree.hpp"

class TileMap
{
public:
	TileMap(const char* s);
	virtual ~TileMap();

    bool IsInbounds(Rectangle* rectangle) const;
    bool IsInbounds(const vec2f& position, float width, float height) const;
    void CollidablesFor(Rectangle* rectangle, std::vector<Rectangle*>& collidables) const;

    void RenderLayers(unsigned int from, unsigned int to) const;
    void RenderLayersBelow() const;
    void RenderLayersAbove() const;
	virtual void Render() const;

protected:
    TMX::Map* map_;
    Quadtree* collidables_;
    std::vector<Rectangle*> blocked_tiles_;

private:
    unsigned int above_index;
    GLuint texture;
};
