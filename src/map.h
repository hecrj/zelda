#pragma once

#include <string>
#include "TMXParser.h"

class Map
{
public:
	Map(const std::string &s);
	virtual ~Map(void);

	void Render();

private:
    TMX::Parser parser;
};
