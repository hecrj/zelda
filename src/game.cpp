#define GL_GLEXT_PROTOTYPES 1

#include <sstream>
#include <iostream>
#include "game.hpp"
#include "utils.hpp"
#include "debug.hpp"
#include "entity/mob/link_follower.hpp"
#include "entity/mob/guard.hpp"
#include "entity/mob/stalfos.hpp"
#include "entity/item/rupee.hpp"
#include "graphic/effect/fade.hpp"
#include "audio/music.hpp"
#include "audio/sound.hpp"
#include "entity/object/plant.hpp"
#include "entity/door.hpp"
#include "screen/level_screen.hpp"
#include "screen/title_screen.hpp"
#include "graphic/font.hpp"
#include "screen/over_screen.hpp"
#include "entity/mob/moldorm.hpp"
#include "entity/item/key.hpp"

const unsigned char Game::ACTION_KEY = 'z';
const int Game::SCALE = 2;
const int Game::MIN_WINDOW_WIDTH = 800;
const int Game::MIN_WINDOW_HEIGHT = 600;
const int Game::MIN_WIDTH = MIN_WINDOW_WIDTH / SCALE;
const int Game::MIN_HEIGHT = MIN_WINDOW_HEIGHT / SCALE;

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
    Font::Load();
    TitleScreen::Load();
    Level::Load();
    Hud::Load();
    Link::Load();
    LinkFollower::Load();
    Guard::Load();
    Stalfos::Load();
    Moldorm::Load();
    Rupee::Load();
    Key::Load();
    Plant::Load();
    Door::Load();

    LoadLevel("overworld");
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
    if(width < MIN_WINDOW_WIDTH) {
        glutReshapeWindow(MIN_WINDOW_WIDTH, height);
        return;
    }

    if(height < MIN_WINDOW_HEIGHT) {
        glutReshapeWindow(width, MIN_WINDOW_HEIGHT);
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
    ChangeScreen(new TitleScreen());
}

void Game::LoadLevel(const char* name) {
    ChangeScreen(new LevelScreen(keys, name));
}

void Game::Over(const std::string& from_level_name) {
    ChangeScreen(new OverScreen(from_level_name));
}

void Game::Exit() {
    std::exit(0);
}

bool Game::ConsumeKey(const char key) {
    bool value = keys[key];
    keys[key] = false;
    return value;
}

bool Game::KeyStatus(const char key) const {
    return keys[key];
}
