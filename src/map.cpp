#include "map.h"
#include <GL/glut.h>
#include <sstream>
#include <iostream>

Map::Map(const std::string &s)
{
    std::stringstream path;
    path << "/home/hector/projects/zelda/res/level/" << s << ".tmx";
    parser.load(path.str().c_str());
}

Map::~Map(void)
{
}

void Map::Render()
{

}
