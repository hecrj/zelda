#include "game.h"
#include "utils.h"
#include <GL/glut.h>
#include <iostream>

Game::Game(void)
{
    t = 0.0;
    dt = 0.01;
    current_time = CurrentTime();
    accumulator = 0.0;
}

Game::~Game(void)
{

}

bool Game::Init()
{
	bool res=true;

	//Graphics initialization
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

    glOrtho(0, GAME_WIDTH, GAME_HEIGHT, 0, 0, 1);

	glMatrixMode(GL_MODELVIEW);

	return res;
}

void Game::Loop()
{
    double newTime = CurrentTime();
    double frame_time = newTime - current_time;

    std::cout << "N: " << newTime << std::endl;

    current_time = newTime;
    accumulator += frame_time;

    while(accumulator >= dt)
    {
        Process(dt);
        accumulator -= dt;
        t += dt;
    }

    std::cout << frame_time << std::endl;

    Render();
}

void Game::Finalize()
{
}

//Input
void Game::ReadKeyboard(unsigned char key, int x, int y, bool press)
{
	keys[key] = press;
}

void Game::ReadMouse(int button, int state, int x, int y)
{

}

//Process
bool Game::Process(double delta)
{
	bool res=true;
	
	//Process Input
	if(keys[27])	res=false;

	return res;
}

//Output
void Game::Render()
{
	glClear(GL_COLOR_BUFFER_BIT);	
	glLoadIdentity();

	//-- TODO: Draw scene

	//--

	glutSwapBuffers();
}
