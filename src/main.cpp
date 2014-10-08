#include <GL/glut.h>
#include "game.h"

//Delete console
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

//-- TODO: Game instance
Game game;
//--

void AppRender()
{
	game.Render();
}

void AppKeyboard(unsigned char key, int x, int y)
{
	game.ReadKeyboard(key,x,y,true);
}

void AppKeyboardUp(unsigned char key, int x, int y)
{
	game.ReadKeyboard(key,x,y,false);
}

void AppSpecialKeys(int key, int x, int y)
{
	game.ReadKeyboard(key,x,y,true);
}

void AppSpecialKeysUp(int key, int x, int y)
{
	game.ReadKeyboard(key,x,y,false);
}

void AppMouse(int button, int state, int x, int y)
{
	game.ReadMouse(button,state,x,y);
}

void AppIdle()
{
    game.Tick();
}

int main(int argc, char** argv)
{
	int res_x,res_y,pos_x,pos_y;

	//GLUT initialization
	glutInit(&argc, argv);

	//RGBA with double buffer
	glutInitDisplayMode(GLUT_RGBA | GLUT_ALPHA | GLUT_DOUBLE);

	//Create centered window
	res_x = glutGet(GLUT_SCREEN_WIDTH);
	res_y = glutGet(GLUT_SCREEN_HEIGHT);
	pos_x = (res_x>>1)-(GAME_WIDTH>>1);
	pos_y = (res_y>>1)-(GAME_HEIGHT>>1);
	
	glutInitWindowPosition(pos_x, pos_y);
	glutInitWindowSize(GAME_WIDTH, GAME_HEIGHT);
	glutCreateWindow("Zelda");

	/*glutGameModeString("800x600:32");
	glutEnterGameMode();*/

	//Make the default cursor disappear
	//glutSetCursor(GLUT_CURSOR_NONE);

	//Register callback functions
	glutDisplayFunc(AppRender);			
	glutKeyboardFunc(AppKeyboard);		
	glutKeyboardUpFunc(AppKeyboardUp);	
	glutSpecialFunc(AppSpecialKeys);	
	glutSpecialUpFunc(AppSpecialKeysUp);
	glutMouseFunc(AppMouse);
	glutIdleFunc(AppIdle);

	//-- TODO: Game initializations
	game.Init();
	//--

	//-- TODO: Application loop
	glutMainLoop();
	//--
}
