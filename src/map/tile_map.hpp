#pragma once

#include "tmx_map.hpp"
#include "GL/glut.h"

class TileMap
{
public:
	TileMap(const char* s);
	virtual ~TileMap();

    virtual void Update(double delta);
	virtual void Render();

private:
    TMX::Map* map;
    GLuint texture;
};
