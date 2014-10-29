#pragma once

#include "map/level.hpp"
#include "hud.hpp"

class Game : public Drawable
{
public:
    typedef Drawable super;
    static int WIDTH;
    static int HEIGHT;
    static bool DIRTY;
    static Rectangle RECTANGLE;
    static GLuint FramebufferAux();
    static void Error(const char* error, const std::string& wat);
	Game();
	virtual ~Game();

	void Init();
	void Tick();
	void Finalize();

	void ReadKeyboard(unsigned char key, int x, int y, bool press);
	void ReadMouse(int button, int state, int x, int y);
    void Update(double delta);
	void Draw() const;
    void Reshape(int width, int height);

private:
    static GLuint FRAMEBUFFER_AUX;
    static GLuint RENDERBUFFER_AUX;

	bool keys[256];
	Level* level;
    Hud* hud;

    // Timing variables
    double t;
    double dt;
    double current_time;
    double accumulator;
};
