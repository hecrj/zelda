#include "game.hpp"
#include "utils.hpp"
#include "entity/mob/link.hpp"
#include "entity/mob/ai/player.hpp"
#include <GL/glut.h>

Game::Game()
{
    t = 0.0;
    dt = 0.01;
    current_time = CurrentTime();
    accumulator = 0.0;

    for(int i = 0; i < 256; ++i) {
        keys[i] = false;
    }
}

Game::~Game()
{
    if(level != NULL)
        delete level;
}

void Game::Init()
{
	//Graphics initialization
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    glOrtho(0, GAME_WIDTH, GAME_HEIGHT, 0, 0, 1);

	glMatrixMode(GL_MODELVIEW);

    // Load demo map
    level = new Level("demo");

    Link::Load();
    Link* link = new Link(level);
    Player* player = new Player(link, keys);
    link->set_AI(player);

    level->AddEntity(link);
}

void Game::Tick()
{
    double newTime = CurrentTime();
    double frame_time = newTime - current_time;

    current_time = newTime;
    accumulator += frame_time;

    while(accumulator >= dt) {
        Update(dt);
        accumulator -= dt;
        t += dt;
    }

    glutPostRedisplay();
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
void Game::Update(double delta)
{
	level->Update(delta);
}

//Output
void Game::Render()
{
	glClear(GL_COLOR_BUFFER_BIT);	
	glLoadIdentity();

	level->Render();

	glutSwapBuffers();
}
