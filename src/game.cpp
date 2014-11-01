#define GL_GLEXT_PROTOTYPES 1

#include <sstream>
#include <iostream>
#include "game.hpp"
#include "utils.hpp"
#include "entity/mob/link.hpp"
#include "entity/mob/ai/player.hpp"
#include "entity/mob/ai/follower.hpp"
#include "debug.hpp"
#include "entity/mob/guard.hpp"
#include "entity/mob/ai/chase.hpp"
#include "entity/mob/stalfos.hpp"
#include "hud.hpp"
#include "entity/item/rupee.hpp"
#include "graphic/effect/fade.hpp"
#include "audio/music.hpp"
#include "audio/sound.hpp"
#include "entity/object/plant.hpp"
#include "entity/door.hpp"
#include "screen/level_screen.hpp"
#include "screen/title_screen.hpp"

const int Game::SCALE = 2;
int Game::WINDOW_WIDTH = 1024;
int Game::WINDOW_HEIGHT = 768;
int Game::WIDTH = Game::WINDOW_WIDTH / Game::SCALE;
int Game::HEIGHT = Game::WINDOW_HEIGHT / Game::SCALE;
bool Game::DIRTY = true;
Rectangle Game::RECTANGLE = Rectangle(0, 0, Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT);
GLuint Game::FRAMEBUFFER_AUX = 0;
GLuint Game::RENDERBUFFER_AUX = 0;
Game Game::INSTANCE;

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
        glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA8, WINDOW_WIDTH, WINDOW_HEIGHT);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);
        glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, render_buf);

        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);

        RENDERBUFFER_AUX = render_buf;
        FRAMEBUFFER_AUX = fbo;
    }

    return FRAMEBUFFER_AUX;
}

void Game::Error(const char* error, const std::string& wat) {
    std::stringstream ss;
    ss << error << ' ' << wat;

    std::cerr << ss.str() << std::endl;
    std::exit(1);
}

Game::Game()
{
    screen = 0;
    old_screen = 0;
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
    if(screen)
        delete screen;

    if(old_screen)
        delete old_screen;
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
    glOrtho(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, 1);
	glMatrixMode(GL_MODELVIEW);

    // Set seed
    srand((unsigned) time(NULL));

    // Load game resources
    TitleScreen::Load();
    Hud::Load();
    Link::Load();
    Guard::Load();
    Stalfos::Load();
    Rupee::Load();
    Plant::Load();
    Door::Load();

    ChangeScreen(new TitleScreen(keys));
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

void Game::ReadKeyboard(unsigned char key, int x, int y, bool press)
{
	keys[key] = press;

    if(key == 'a' && press)
        Debug::enabled = !Debug::enabled;
}

void Game::ReadMouse(int button, int state, int x, int y)
{

}

void Game::Update(double delta)
{
    Music::Update(delta);
    Sound::Update(delta);

    screen->Tick(delta);
}

void Game::Render() const
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    screen->Render();

    glutSwapBuffers();
}

void Game::Reshape(int width, int height) {
    if(width < 800) {
        glutReshapeWindow(800, height);
        return;
    }

    if(height < 600) {
        glutReshapeWindow(width, 600);
        return;
    }

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, height, 0, 0, 1);
    glMatrixMode(GL_MODELVIEW);

    WINDOW_WIDTH = width;
    WINDOW_HEIGHT = height;
    WIDTH = WINDOW_WIDTH / SCALE;
    HEIGHT = WINDOW_HEIGHT / SCALE;
    RECTANGLE = Rectangle(0, 0, WIDTH, HEIGHT);
    DIRTY = true;
}

void Game::ChangeScreen(Screen* screen) {
    if(old_screen)
        delete old_screen;

    old_screen = this->screen;
    this->screen = screen;
    this->screen->Init();
}

void Game::LoadTitleScreen() {
    ChangeScreen(new TitleScreen(keys));
}

void Game::LoadLevel(const char* name) {
    ChangeScreen(new LevelScreen(keys, name));
}

void Game::Over() {
    // TODO: Game over screen
}

void Game::Exit() {
    std::exit(0);
}
