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

public:

	std::vector<float> _position;
	std::vector<float> _rotation;

	Robot();
	Robot(std::vector<float> position, std::vector<float> rotation);

	void shakeHead();
	void randomColor();
	void setColor(float r, float g, float b);

	~Robot();

	void draw();

};

class Robot::Leg {
public:
	Leg(Robot* _robot, std::vector<float> offset_pos, std::vector<float> offset_rot);
	void draw();
	void randomColor();
	void setColor(float r, float g, float b);
private:
	Robot* _robot;

	std::vector<unsigned char>   _color;
	std::vector<float> _offset_pos;
	std::vector<float> _offset_rot;
};

class Robot::Arm {
public:
	Arm(Robot* _robot, std::vector<float> offset_pos, std::vector<float> offset_rot);
	void draw();
	void randomColor();
	void setColor(float r, float g, float b);
private:
	Robot* _robot;

	std::vector<unsigned char> _color;
	std::vector<float> _offset_pos;
	std::vector<float> _offset_rot;
};

class Robot::Torso {
public:
	Torso(Robot* _robot, std::vector<float> offset_pos, std::vector<float> offset_rot);
	void draw();
	void randomColor();
	void setColor(float r, float g, float b);
private:
	Robot* _robot;

	std::vector<unsigned char>   _color;
	std::vector<float> _offset_pos;
	std::vector<float> _offset_rot;
};

class Robot::Head {
public:
	Head(Robot* _robot, std::vector<float> offset_pos, std::vector<float> offset_rot);
	void draw();
	void shake();
	void randomColor();
	void setColor(float r, float g, float b);
private:
	Robot* _robot;

	std::vector<unsigned char>   _color;
	std::vector<float> _offset_pos;
	std::vector<float> _offset_rot;
};


#endif