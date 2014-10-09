#pragma once

#include "tmx_map.hpp"
#include "GL/glut.h"

class Map
{
public:
	Map(const char* s);
	virtual ~Map();

	void Render();

private:
    TMX::Map* map;
    GLuint texture;
};
