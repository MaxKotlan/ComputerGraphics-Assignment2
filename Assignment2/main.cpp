#include <GL/glut.h>

#include "robot.h"
#include <time.h>

#define WIN_W 1920
#define WIN_H 1080

GLfloat rot = .01;
bool bXaxis = false;
bool bYaxis = false;
bool bZaxis = false;
bool bMouseDown = false;

Robot robot;

void myDisplay(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);

	
	
	if (!bMouseDown)
	{
		if (bXaxis) glRotatef(rot, 1.0f, 0.0f, 0.0f);
		else if (bYaxis) glRotatef(rot, 0.0f, 1.0f, 0.0f);
		else if (bZaxis) glRotatef(rot, 0.0f, 0.0f, 1.0f);
		else glRotatef(rot, 1.0f, 1.0f, 1.0f);
	} 

	//glRotatef(rot, 0.0f, 1.0f, 0.0f);

	robot.draw();
	glFlush();
}

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-WIN_W / 2, WIN_W / 2, -WIN_H / 2,
		WIN_H / 2, -100, 100);
}

void procKeys(unsigned char key, int x, int y)
{
	switch (key) {
	case 'x': bXaxis = true; bYaxis = false;
		bZaxis = false;  break;
	case 'y': bYaxis = true; bXaxis = false;
		bZaxis = false;  break;
	case 'z': bZaxis = true; bXaxis = false;
		bYaxis = false; break;
	case 'i': rot += .1; // increment the rotation
	case 27: exit(0); break;
	}
}

void procMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		bMouseDown = true;
	else bMouseDown = false;
}

int main(int argc, char** argv) {

	srand(time(nullptr));

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WIN_W, WIN_H);
	glutCreateWindow("Ex4 ‐ Object Rotation with the mouse");
	init();
	glutDisplayFunc(myDisplay);
	glutIdleFunc(myDisplay);
	glutKeyboardFunc(procKeys);
	glutMouseFunc(procMouse);
	glutMainLoop();
	return 0;
}