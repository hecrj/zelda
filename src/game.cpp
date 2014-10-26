#define GL_GLEXT_PROTOTYPES 1
#include "game.hpp"
#include "utils.hpp"
#include "entity/mob/link.hpp"
#include "entity/mob/ai/player.hpp"
#include "entity/mob/ai/follower.hpp"
#include "debug.hpp"
#include "entity/mob/guard.hpp"
#include "entity/mob/ai/chase.hpp"
#include "entity/mob/stalfos.hpp"

int Game::WIDTH = 640;
int Game::HEIGHT = 480;
bool Game::DIRTY = true;
GLuint Game::FRAMEBUFFER_AUX = 0;
GLuint Game::RENDERBUFFER_AUX = 0;

GLuint Game::FramebufferAux() {
    if(FRAMEBUFFER_AUX and DIRTY) {
        glDeleteRenderbuffers(1, &RENDERBUFFER_AUX);
        glDeleteFramebuffers(1, &FRAMEBUFFER_AUX);

        FRAMEBUFFER_AUX = 0;
        RENDERBUFFER_AUX = 0;
        DIRTY = false;
    }

    if(!FRAMEBUFFER_AUX) {
        GLuint fbo, render_buf;
        glGenFramebuffers(1, &fbo);
        glGenRenderbuffers(1, &render_buf);
        glBindRenderbuffer(GL_RENDERBUFFER, render_buf);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA8, WIDTH, HEIGHT);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);
        glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, render_buf);

        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);

        RENDERBUFFER_AUX = render_buf;
        FRAMEBUFFER_AUX = fbo;
    }

    return FRAMEBUFFER_AUX;
}

Game::Game()
{
    t = 0.0;
    dt = 0.016;
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
    glOrtho(0, WIDTH, HEIGHT, 0, 0, 1);

	glMatrixMode(GL_MODELVIEW);

    // Set seed
    srand((unsigned) time(NULL));

    // Load demo map
    level = new Level("bigger");

    Link::Load();
    Guard::Load();
    Stalfos::Load();

    Link* link = new Link(level);
    Link* link2 = new Link(level);
    Guard* guard = new Guard(level);
    Stalfos* stalfos = new Stalfos(level);

    link->set_position(17 * 16, 17 * 16);
    link2->set_position(17 * 16, 11 * 16);
    guard->set_position(20 * 16, 11 * 16);
    stalfos->set_position(22 * 16, 11 * 16);

    Player* player = new Player(link, keys);
    link->set_AI(player);
    link2->set_AI(new Follower(link2));
    guard->set_AI(new Chase(guard));
    stalfos->set_AI(new Chase(stalfos));

    level->AddPlayer(link);
    level->AddEntity(link2);
    level->AddEntity(guard);
    level->AddEntity(stalfos);
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

    if(key == 'a' && press)
        Debug::enabled = !Debug::enabled;
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

void Game::Reshape(int width, int height) {
    if(width < 640) {
        glutReshapeWindow(640, height);
        return;
    }

    if(height < 480) {
        glutReshapeWindow(width, 480);
        return;
    }

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, height, 0, 0, 1);
    glMatrixMode(GL_MODELVIEW);

    WIDTH = width;
    HEIGHT = height;
    DIRTY = true;
}
