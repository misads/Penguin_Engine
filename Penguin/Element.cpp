#include "stdafx.h"
#include "Element.h"


CElement::CElement()
{
}

CElement::~CElement()
{
}

int CElement::Getdirection(){
	return m_direction;
}
void CElement::Setdirection(int _direction){
	m_direction = _direction;
}


fPoint CElement::Getpos(){
	return m_pos;
}
void CElement::Setpos(fPoint _pos){
	m_pos = _pos;
}

float CElement::Getspeed(){
	return m_speed;
}
void CElement::Setspeed(float _speed){
	m_speed = _speed;
}


void CElement::Move(int direction, float _pixel){
	if (direction == 1)m_pos = fPoint(m_pos.x, m_pos.y - _pixel);
	if (direction == 2)m_pos = fPoint(m_pos.x, m_pos.y + _pixel);
	if (direction == 3)m_pos = fPoint(m_pos.x - _pixel, m_pos.y);
	if (direction == 4)m_pos = fPoint(m_pos.x + _pixel, m_pos.y);

}

