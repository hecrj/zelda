#pragma once

#include "tmx_map.hpp"
#include "GL/glut.h"

class TileMap
{
public:
	TileMap(const char* s);
	virtual ~TileMap();

    void Update(double delta);
	void Render();

private:
    TMX::Map* map;
    GLuint texture;
};
