#pragma once

#include "map/level.hpp"
#include "hud.hpp"
#include "screen.hpp"

class Game
{
public:
    static const unsigned char ACTION_KEY;
    static const int SCALE;
    static int WINDOW_WIDTH;
    static int WINDOW_HEIGHT;
    static int WIDTH;
    static int HEIGHT;
    static bool DIRTY;
    static Rectangle RECTANGLE;
    static Game INSTANCE;

    static GLuint FramebufferAux();
    static void Error(const char* error, const std::string& wat);

	Game();
	virtual ~Game();

    bool ConsumeKey(const char key);
    bool KeyStatus(const char key) const;

	void Init();
	void Tick();
	void Finalize();

    void LoadTitleScreen();
    void LoadLevel(const char* name);
    void Over();
    void Exit();

	void ReadKeyboard(unsigned char key, int x, int y, bool press);
	void ReadMouse(int button, int state, int x, int y);
    void Update(double delta);
	void Render() const;
    void Reshape(int width, int height);

private:
    static GLuint FRAMEBUFFER_AUX;
    static GLuint RENDERBUFFER_AUX;

	bool keys[256];
    Screen* screen;
    Screen* old_screen;

    // Timing variables
    double t;
    double dt;
    double current_time;
    double accumulator;

    void ChangeScreen(Screen* screen);
};
