
#include "scene.h"
#include <GL/glut.h>

Scene::Scene(void)
{
}

Scene::~Scene(void)
{
}

void Scene::Draw()
{
	//-- TODO: Draw something
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f,0.0f,0.0f);	glVertex2i(100,100);

	glEnd();
	//--
}
