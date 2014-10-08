#pragma once

#include "map.hpp"

#define GAME_WIDTH	640
#define GAME_HEIGHT 480

class Game
{
public:
	Game();
	virtual ~Game();

	bool Init();
	void Tick();
	void Finalize();

	//Input
	void ReadKeyboard(unsigned char key, int x, int y, bool press);
	void ReadMouse(int button, int state, int x, int y);
	//Process
    bool Process(double delta);
	//Output
	void Render();

private:
	unsigned char keys[256];
	Map* map;

    // Timing variables
    double t;
    double dt;
    double current_time;
    double accumulator;
};
