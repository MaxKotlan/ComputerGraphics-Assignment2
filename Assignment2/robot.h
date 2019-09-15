#ifndef ROBOT_H
#define ROBOT_H

#include <vector>

class Robot {
private:
	class Leg;
	class Arm;
	class Torso;
	class Head;

	Leg*   _leftleg;
	Leg*   _rightleg;
	Arm*   _leftarm;
	Arm*   _rightarm;
	Torso* _torso;
	Head*  _head;

	std::vector<float> _position;
	std::vector<float> _rotation;
public:
	Robot();
	Robot(std::vector<float> position, std::vector<float> rotation);

	~Robot();

	void draw();

};

class Robot::Leg {
public:
	Leg(Robot* _robot, std::vector<float> offset_pos, std::vector<float> offset_rot);
	void draw();
private:
	Robot* _robot;

	std::vector<float> _offset_pos;
	std::vector<float> _offset_rot;
};

#endif