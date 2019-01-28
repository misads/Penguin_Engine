#pragma once

class CElement
{
public:
	CElement();
	~CElement();

	int Getdirection();
	void Setdirection(int _direction);

	fPoint Getpos();
	void Setpos(fPoint _pos);

	float Getspeed();
	void Setspeed(float _speed);

	void Move(int direction, float _pixel);



private:
	int m_direction;
	fPoint m_pos;
	float m_speed;
};

