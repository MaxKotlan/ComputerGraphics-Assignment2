#include <GL/freeglut.h>

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

bool wireframe = false;
bool clear = false;

/*Number of robots to be created (in rows and columns)*/
const int numRobots_x = 15;
const int numRobots_z = 70;

/*Space between each robot*/
const int robot_spacing_x = 250;
const int robot_spacing_z = 100;

/*Array of robots*/
Robot robot[numRobots_x][numRobots_z];


/*Draw xyz axis*/
void drawAxis() {
	glBegin(GL_LINES);
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(100.0f, -0.0f, -0.0f);
	glEnd();
	glBegin(GL_LINES);
		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 100.0f, -0.0f);
	glEnd();
	glBegin(GL_LINES);
		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 100.0f);
	glEnd();
}

void myDisplay(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);

	/*Render models as wireframe*/
	if (wireframe)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


	if (bMouseDown) {
		/*Loop through all robots and set color to random
		 in the homework it says to toggle white, but this is really challenging to
		 set up, for this design, and i think shuffling the color randomly is better
		 looking
		*/
		for (int x = 0; x < numRobots_x; x++)
			for (int z = 0; z < numRobots_z; z++)
					robot[x][z].randomColor();
	}

	/*rotate camera*/
	glRotatef(rot, 1.0f, 1.0f, 1.0f);

	/*Loop through each robot, 
		calculate its position (based on its index),
		call shakeHead() to update the rotation of its head
		call draw, to draw all the bodyparts (head, arms, legs, torso)
	*/
	for (int x = 0; x < numRobots_x; x++) {
		for (int z = 0; z < numRobots_z; z++) {
			robot[x][z]._position[0] = x * robot_spacing_x - (numRobots_x  * robot_spacing_x)/2;
			robot[x][z]._position[2] = z * robot_spacing_z - (numRobots_z * robot_spacing_z)/2;

			/*could not get this rotation to work like I wanted to*/
			//robot[x][z]._rotation[0] = rot; 
			//robot[x][z]._rotation[1] = 0.01;

			robot[x][z].shakeHead();
			robot[x][z].draw();
		}
	}


	/*if c is clicked, clear the screen, so nothing is rendered except for the world axis*/
	if (clear)
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	drawAxis();


	/*flush the buffer for the next frame*/
	glFlush();
}

void init(void)
{
	/*background color black*/
	glClearColor(.1, 0.1, 0.1, 0.0);

	/*depth test, so that robots are rendered properly*/
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glViewport(0, 0, WIN_W, WIN_H);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	/*camera orrientation*/
	if (perspective) 
		gluPerspective(90., WIN_W / WIN_H + 1.0, 0.1, 10000.);
	else
		glOrtho(-WIN_W / 2, WIN_W / 2, -WIN_H / 2,
		WIN_H / 2, -30000, 10000); 

	/*change camera position and what its looking at*/
	gluLookAt(0, 400.0, -500.0, 0, 60., 0, 0, 1, 0);
}

void mouseWheel(int wheel, int direction, int x, int y) {

	/*I couldnt come up with a good way to zoom in, so this is what I'm doing instead*/
	if (direction > 0) gluLookAt(-1000, 0.0, 0.0, 0, 0, 0, 0, 1, 0);

	glutPostRedisplay();
}

/*If window size changes, recall init with updated windowsize*/
void onreshape(int width, int height) {
	WIN_W = width;
	WIN_H = height;
	init();
}

/*Process Menu Click*/
void menu(int num) {

	switch (num) {
		case 0: exit(0); break;
		case 2: 

			/*Loop through all robots and call random color*/
			for (int x = 0; x < numRobots_x; x++)
				for (int z = 0; z < numRobots_z; z++)
					robot[x][z].randomColor();
			break;

		case 3:

			/*Loop through all robots and set color to red*/
			for (int x = 0; x < numRobots_x; x++)
				for (int z = 0; z < numRobots_z; z++)
					robot[x][z].setColor(1.0,0.0,0.0);
			break;

		case 4:

			/*Loop through all robots and set color to green*/
			for (int x = 0; x < numRobots_x; x++)
				for (int z = 0; z < numRobots_z; z++)
					robot[x][z].setColor(0.0, 1.0, 0.0);
			break;

		case 5:

			/*Loop through all robots and set color to blue*/
			for (int x = 0; x < numRobots_x; x++)
				for (int z = 0; z < numRobots_z; z++)
					robot[x][z].setColor(0.0, 0.0, 1.0);
			break;

		case 6:

			/*Loop through all robots and set color to white*/
			for (int x = 0; x < numRobots_x; x++)
				for (int z = 0; z < numRobots_z; z++)
					robot[x][z].setColor(1.0, 1.0, 1.0);
			break;


		case 7: perspective = false; init(); break;
		case 8: perspective =  true; init(); break;

	}
	
	/* send an event to update the screen */
	glutPostRedisplay();

}

/*Creates Menu Layout*/
void createMenu(void) {

	static int menu_id;
	static int colormenu_id;
	static int projection_menu_id;


	colormenu_id = glutCreateMenu(menu);

	glutAddMenuEntry("Random", 2);

	glutAddMenuEntry("Red",    3);

	glutAddMenuEntry("Green",  4);

	glutAddMenuEntry("Blue",   5);

	glutAddMenuEntry("White",  6);

	projection_menu_id = glutCreateMenu(menu);

	glutAddMenuEntry("Orthographic", 7);

	glutAddMenuEntry("Perspective",  8);


	menu_id = glutCreateMenu(menu);

	glutAddMenuEntry("Clear", 1);

	glutAddSubMenu("Color", colormenu_id);
	glutAddSubMenu("Projection", projection_menu_id);

	glutAddMenuEntry("Quit", 0);

	glutAttachMenu(GLUT_RIGHT_BUTTON);

}

/*Process keyboard input*/
void procKeys(unsigned char key, int x, int y)
{
	switch (key) {
	case 'x': bXaxis = true; bYaxis = false;
		bZaxis = false;  break;
	case 'y': bYaxis = true; bXaxis = false;
		bZaxis = false;  break;
	case 'z': bZaxis = true; bXaxis = false;
		bYaxis = false; break;
	case 'w': wireframe = true; break;
	case 's': wireframe = false; break;
	case 'c': clear = true; break;
	case 'm': clear = false; break;
	case 'i': rot += .1; break; // increment the camera rotation speed
	case 'o': rot -= .1; break; // decrement the camera rotation speed
	case 'p': perspective = !perspective; init(); break;
	case 27: exit(0); break;
	}
}

/*process mouse*/
void procMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		bMouseDown = true;
	else bMouseDown = false;
}

/*main function. Application starts here*/
int main(int argc, char** argv) {

	srand(time(nullptr));

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WIN_W, WIN_H);
	glutCreateWindow("Maxwell Kotlan");
	glutMouseWheelFunc(mouseWheel);
	createMenu();
	init();
	glutDisplayFunc(myDisplay);
	glutIdleFunc(myDisplay);
	glutReshapeFunc(onreshape);
	glutKeyboardFunc(procKeys);
	glutMouseFunc(procMouse);
	glutMainLoop();
	return 0;
}