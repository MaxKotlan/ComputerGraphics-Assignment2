#include "robot.h"
#include <GL/glut.h>

Robot::Robot() {
	std::vector <float> nullpos    = {   0.0,   0.0, 0.0 }; std::vector <float> nullrot = { 0.0, 0.0, 0.0, 0.0 };

	std::vector <float> llegpos = { -30.0, -70.0, 0.0 }; //std::vector <float> llegrot = { 90.0, 1.0, 0.0, 0.0 };
	std::vector <float> rlegpos = {  30.0, -70.0, 0.0 }; //std::vector <float> llegrot = { 90.0, 1.0, 0.0, 0.0 };
	std::vector <float> larmpos = { -70.0,  30.0, 0.0 }; std::vector <float> larmrot = { 90.0, 0.0, 1.0, 0.0 };
	std::vector <float> rarmpos = {  70.0,  30.0, 0.0 }; std::vector <float> rarmrot = { 90.0, 0.0, 1.0, 0.0 };
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


Robot::Robot(std::vector<float> position, std::vector<float> rotation){
	_position = position;
	_rotation = rotation;
	Robot();
}

Robot::~Robot() {
	delete _leftleg;
	delete _rightleg;
	delete _leftarm;
	delete _rightarm;
	delete _torso;
	delete _head;
}

void Robot::draw() {
	_leftleg->draw();
	_rightleg->draw();
	_leftarm->draw();
	_rightarm->draw();
	_torso->draw();
	_head->draw();
	
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

Robot::Head::Head(Robot* robot, std::vector<float> offset_pos, std::vector<float> offset_rot) {
	_robot = robot;
	_offset_pos = offset_pos;
	_offset_rot = offset_rot;

	_color = { unsigned char(rand() % 255), unsigned char(rand() % 255), unsigned char(rand() % 255) };
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

	glutSolidTeapot(30);
	glPopMatrix();
}