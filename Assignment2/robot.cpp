#include "robot.h"
#include <GL/glut.h>

/*Default Robot constructor
Creates all the body parts of the robot at the origin,
then offsets them to so they're in the right postition and rotation
*/
Robot::Robot() {
	std::vector <float> nullpos    = {   0.0,   0.0, 0.0 }; std::vector <float> nullrot = { 0.0, 0.0, 0.0, 0.0 };

	std::vector <float> llegpos = { -30.0, -75.0, 0.0 }; //std::vector <float> llegrot = { 90.0, 1.0, 0.0, 0.0 };
	std::vector <float> rlegpos = {  30.0, -75.0, 0.0 }; //std::vector <float> llegrot = { 90.0, 1.0, 0.0, 0.0 };
	std::vector <float> larmpos = { -75.0,  30.0, 0.0 }; std::vector <float> larmrot = { 90.0, 0.0, 1.0, 0.0 };
	std::vector <float> rarmpos = {  75.0,  30.0, 0.0 }; std::vector <float> rarmrot = { 90.0, 0.0, 1.0, 0.0 };
	std::vector <float> torspos = {   0.0,   0.0, 0.0 }; //std::vector <float> llegrot = { 90.0, 1.0, 0.0, 0.0 };
	std::vector <float> headpos = {   0.0,  60.0, 0.0 }; std::vector <float> headrot = { 90.0, 0.0, 1.0, 0.0 };


	_position = nullpos;
	_rotation = nullrot;

	_leftleg  = new Leg  (this, llegpos, nullrot);
	_rightleg = new Leg  (this, rlegpos, nullrot);
	_leftarm  = new Arm  (this, larmpos, larmrot);
	_rightarm = new Arm  (this, rarmpos, larmrot);
	_torso    = new Torso(this, torspos, nullrot);
	_head     = new Head (this, headpos, headrot);

}

/*
Constructor for robot. Initalizes it with a position and a rotation.
*/
Robot::Robot(std::vector<float> position, std::vector<float> rotation){
	_position = position;
	_rotation = rotation;
	Robot();
}

/*Destructor deletes all dynamically allocated bodyparts*/
Robot::~Robot() {
	delete _leftleg;
	delete _rightleg;
	delete _leftarm;
	delete _rightarm;
	delete _torso;
	delete _head;
}

/*Calls shakehead on the head, to rotate it back and forth*/
void Robot::shakeHead() {
	_head->shake();
}


/*Draw function called in the main draw loop.
calls draw on all the other bodyparts
*/
void Robot::draw() {
	_leftleg->draw();
	_rightleg->draw();
	_leftarm->draw();
	_rightarm->draw();
	_torso->draw();
	_head->draw();
	
}

void Robot::randomColor() {
	_leftleg->randomColor();
	_rightleg->randomColor();
	_leftarm->randomColor();
	_rightarm->randomColor();
	_torso->randomColor();
	_head->randomColor();
}

void Robot::setColor(float r, float g, float b) {
	_leftleg->setColor(r,g,b);
	_rightleg->setColor(r, g, b);
	_leftarm->setColor(r, g, b);
	_rightarm->setColor(r, g, b);
	_torso->setColor(r, g, b);
	_head->setColor(r, g, b);
}

Robot::Leg::Leg(Robot* robot, std::vector<float> offset_pos, std::vector<float> offset_rot) {
	_robot = robot;
	_offset_pos = offset_pos;
	_offset_rot = offset_rot;

	_color = { unsigned char(rand() % 255), unsigned char(rand() % 255), unsigned char(rand() % 255) };
}

void Robot::Leg::draw() {
	/*Translate the position of the leg by the robots position and the offset from the robots position*/
	
	glColor3ub(_color[0], _color[1], _color[2]);

	glPushMatrix();
	glTranslatef(_robot->_position[0] + _offset_pos[0],
			        _robot->_position[1] + _offset_pos[1], 
					_robot->_position[2] + _offset_pos[2]);

	glRotatef(_robot->_rotation[0] + _offset_rot[0],
		_robot->_rotation[1] + _offset_rot[1],
		_robot->_rotation[2] + _offset_rot[2],
		_robot->_rotation[3] + _offset_rot[3]);

	glScaled(1.0, 2.0, 1.0);
	glutSolidCube(30);
	glPopMatrix();
}

void Robot::Leg::randomColor() {
	_color = { unsigned char(rand() % 255), unsigned char(rand() % 255), unsigned char(rand() % 255) };
}

void Robot::Leg::setColor(float r, float g, float b) {
	_color = { unsigned char(r * 255.), unsigned char(g * 255), unsigned char(b * 255) };
}


Robot::Arm::Arm(Robot* robot, std::vector<float> offset_pos, std::vector<float> offset_rot) {
	_robot = robot;
	_offset_pos = offset_pos;
	_offset_rot = offset_rot;

	_color = { unsigned char(rand() % 255), unsigned char(rand() % 255), unsigned char(rand() % 255) };
}

void Robot::Arm::draw() {
	/*Translate the position of the arm by the robots position and the offset from the robots position*/
	glColor3ub(_color[0], _color[1], _color[2]);

	glPushMatrix();
	glTranslatef(_robot->_position[0] + _offset_pos[0],
				 _robot->_position[1] + _offset_pos[1],
				 _robot->_position[2] + _offset_pos[2]);

	glRotatef(_robot->_rotation[0] + _offset_rot[0],
		_robot->_rotation[1] + _offset_rot[1],
		_robot->_rotation[2] + _offset_rot[2],
		_robot->_rotation[3] + _offset_rot[3]);

	glScaled(1.0, 1.0, 2.0);
	glutSolidCube(30);
	glPopMatrix();
}

void Robot::Arm::randomColor() {
	_color = { unsigned char(rand() % 255), unsigned char(rand() % 255), unsigned char(rand() % 255) };
}

void Robot::Arm::setColor(float r, float g, float b) {
	_color = { unsigned char(r * 255.), unsigned char(g * 255.), unsigned char(b * 255.) };
}


Robot::Torso::Torso(Robot* robot, std::vector<float> offset_pos, std::vector<float> offset_rot) {
	_robot = robot;
	_offset_pos = offset_pos;
	_offset_rot = offset_rot;

	_color = { unsigned char(rand() % 255), unsigned char(rand() % 255), unsigned char(rand() % 255) };
}

void Robot::Torso::draw() {
	/*Translate the position of the arm by the robots position and the offset from the robots position*/
	
	glColor3ub(_color[0], _color[1], _color[2]);

	glPushMatrix();
	glTranslatef(_robot->_position[0] + _offset_pos[0],
		         _robot->_position[1] + _offset_pos[1],
		         _robot->_position[2] + _offset_pos[2]);


	glRotatef(_robot->_rotation[0] + _offset_rot[0],
		_robot->_rotation[1] + _offset_rot[1],
		_robot->_rotation[2] + _offset_rot[2],
		_robot->_rotation[3] + _offset_rot[3]);

	glScaled(3.0, 3.0, 1.0);
	glutSolidCube(30);
	glPopMatrix();
}

void Robot::Torso::randomColor() {
	_color = { unsigned char(rand() % 255), unsigned char(rand() % 255), unsigned char(rand() % 255) };
}

void Robot::Torso::setColor(float r, float g, float b) {
	_color = { unsigned char(r * 255.), unsigned char(g * 255.), unsigned char(b * 255.) };
}


Robot::Head::Head(Robot* robot, std::vector<float> offset_pos, std::vector<float> offset_rot) {
	_robot = robot;
	_offset_pos = offset_pos;
	_offset_rot = offset_rot;

	_color = { unsigned char(rand() % 255), unsigned char(rand() % 255), unsigned char(rand() % 255) };
}

bool lookLeft = true;

/*Really bad way to deal with rotating head.
increases the rotation by 1 degree each frame, until it becomes greater than 120 degrees.
if it becomes greater than 120 degrees decrease rotation (to switch head shake direction)
*/
void Robot::Head::shake() {
	//_offset_rot[0] = float(int(_offset_rot[0] + 1.0) % 120); //( _offset_rot[0] + 1.0 )%120;

	_offset_rot[0] += 1.0;

	if (!lookLeft)
		_offset_rot[0] -= 2.0;
	
	if (_offset_rot[0] > 120)
		lookLeft = false;
	if (_offset_rot[0] < 60)
		lookLeft = true; 
}

void Robot::Head::draw() {
	/*Translate the position of the head by the robots position and the offset from the robots position*/
	
	glColor3ub(_color[0], _color[1], _color[2]);
	
	glPushMatrix();

	glTranslatef(_robot->_position[0] + _offset_pos[0],
		         _robot->_position[1] + _offset_pos[1],
		         _robot->_position[2] + _offset_pos[2]);
	
	glRotatef(_robot->_rotation[0] + _offset_rot[0],
		      _robot->_rotation[1] + _offset_rot[1],
		      _robot->_rotation[2] + _offset_rot[2],
		      _robot->_rotation[3] + _offset_rot[3]);

	
	/*I used a teapot instead of a sphere because I thought it looked cooler.*/
	glutSolidTeapot(30);
	glPopMatrix();
}

void Robot::Head::randomColor() {
	_color = { unsigned char(rand() % 255), unsigned char(rand() % 255), unsigned char(rand() % 255) };
}

void Robot::Head::setColor(float r, float g, float b) {
	_color = { unsigned char(r * 255.), unsigned char(g * 255.), unsigned char(b * 255.) };
}