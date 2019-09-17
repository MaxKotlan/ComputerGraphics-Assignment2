#include <GL/glut.h>

#include "robot.h"
#include <time.h>

int WIN_W = 800;
int WIN_H = 600;

GLfloat rot = .1;
bool bXaxis = false;
bool bYaxis = false;
bool bZaxis = false;
bool bMouseDown = false;
bool perspective = false;

int displaytime = 0;

const int numRobots_x = 10;
const int numRobots_z = 90;
const int robot_spacing_x = 250;
const int robot_spacing_z = 100;

Robot robot[numRobots_x][numRobots_z];

void myDisplay(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);

	displaytime++;
	
	if (!bMouseDown)
	{
		if (bXaxis) glRotatef(rot, 1.0f, 0.0f, 0.0f);
		else if (bYaxis) glRotatef(rot, 0.0f, 1.0f, 0.0f);
		else if (bZaxis) glRotatef(rot, 0.0f, 0.0f, 1.0f);
		else glRotatef(rot, 1.0f, 1.0f, 1.0f);
	} 

	//glRotatef(rot, 0.0f, 1.0f, 0.0f);
	for (int x = 0; x < 10; x++) {
		for (int z = 0; z < 50; z++) {
			robot[x][z]._position[0] = x * robot_spacing_x - (numRobots_x  * robot_spacing_x)/2;
			robot[x][z]._position[2] = z * robot_spacing_z - (numRobots_z * robot_spacing_z)/2;
			//robot[x][z]._rotation[0] = rot;
			//robot[x][z]._rotation[1] = 0.01;
			robot[x][z].shakeHead();
			robot[x][z].draw();
		}
	}
	glFlush();
}

void init(void)
{
	glClearColor(.8, 0.8, 0.8, 0.0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glViewport(0, 0, WIN_W, WIN_H);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	
	if (perspective) 
		gluPerspective(90., WIN_W / WIN_H + 1.0, 0.1, 10000.);
	else
		glOrtho(-WIN_W / 2, WIN_W / 2, -WIN_H / 2,
		WIN_H / 2, -30000, 10000); 

	

	glTranslatef(0.0, -400.0, -500.0);
	
}

void onreshape(int width, int height) {
	WIN_W = width;
	WIN_H = height;
	init();
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
	case 'i': rot += .1; break; // increment the rotation
	case 'o': rot -= .1; break; // increment the rotation
	case 'p': perspective = !perspective; init(); break;
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
	glutCreateWindow("Assignment 2");
	init();
	glutDisplayFunc(myDisplay);
	glutIdleFunc(myDisplay);
	glutReshapeFunc(onreshape);
	glutKeyboardFunc(procKeys);
	glutMouseFunc(procMouse);
	glutMainLoop();
	return 0;
}