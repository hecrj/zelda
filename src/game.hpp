#pragma once

#include "map/level.hpp"

#define GAME_WIDTH	640
#define GAME_HEIGHT 480

class Game
{
public:
	Game();
	virtual ~Game();

	void Init();
	void Tick();
	void Finalize();

	void ReadKeyboard(unsigned char key, int x, int y, bool press);
	void ReadMouse(int button, int state, int x, int y);
    void Update(double delta);
	void Render();

private:
	bool keys[256];
	Level* level;

    // Timing variables
    double t;
    double dt;
    double current_time;
    double accumulator;
};
