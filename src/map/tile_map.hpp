#pragma once

#include "tmx_map.hpp"
#include "GL/glut.h"

class TileMap
{
public:
	TileMap(const char* s);
	virtual ~TileMap();

    void RenderLayers(unsigned int from, unsigned int to) const;
    void RenderLayersBelow() const;
    void RenderLayersAbove() const;
	virtual void Render() const;

protected:
    TMX::Map* map_;

private:
    unsigned int above_index;
    GLuint texture;
};
