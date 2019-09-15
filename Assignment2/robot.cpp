#include "robot.h"
#include <GL/glut.h>

Robot::Robot() {
	std::vector <float> nullvec = { 0.0,0.0,0.0 };
	_leftleg  = new Leg(this, nullvec, nullvec);
	_rightleg = new Leg(this, nullvec, nullvec);
	_leftarm = nullptr;
	_rightarm = nullptr;
	_torso = nullptr;
	_head = nullptr;

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

Robot::Leg::Leg(Robot* robot, std::vector<float> offset_pos, std::vector<float> offset_rot) {
	_robot = robot;
	_offset_pos = offset_pos;
	_offset_rot = offset_rot;
}

void Robot::draw() {
	_rightleg->draw();
}


void Robot::Leg::draw() {
	glutWireTeapot(20);
}