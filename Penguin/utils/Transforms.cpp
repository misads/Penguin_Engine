#include"stdafx.h"
#include "Element.h"
#include "Transforms.h"


BaseTransform::BaseTransform(){

}

BaseTransform::~BaseTransform(){

}

void BaseTransform::SetElement(CElement* e){
	m_element = e;
}


Translation::Translation(Direction _d, float _speed){
	int direction = (int)_d;
	m_x_speed = m_x[direction] * _speed;
	m_y_speed = m_y[direction] * _speed;
}

Translation::Translation(float speed_x, float speed_y){
	m_x_speed = speed_x;
	m_y_speed = speed_y;
}

Translation::~Translation(){

}

void Translation::Init(){}

void Translation::Transform(float fTime){

	static float lasttime = 0;

	if (lasttime == 0){
		lasttime = fTime;
		return;
	}

	float delta_time = fTime - lasttime;

	m_element->Move(delta_time * m_x_speed, delta_time * m_y_speed);

	lasttime = fTime;

}


float Translation::m_x[9] = { 0, 0, 0, -1, 1, -half_sqrt2, half_sqrt2, -half_sqrt2, half_sqrt2 };
float Translation::m_y[9] = { 0, -1, 1, 0, 0, -half_sqrt2, -half_sqrt2, half_sqrt2, half_sqrt2 };


AccTranslation::AccTranslation(Direction _d, float _acc, float _speed){
	int direction = (int)_d;
	m_x_speed = m_x[direction] * _speed;
	m_y_speed = m_y[direction] * _speed;
	m_x_acc = m_x[direction] * _acc;
	m_y_acc = m_y[direction] * _acc;
}

AccTranslation::AccTranslation(float acc_x, float acc_y, float speed_x, float speed_y){
	m_x_speed = speed_x;
	m_y_speed = speed_y;
	m_x_acc = acc_x;
	m_y_acc = acc_y;
}

AccTranslation::~AccTranslation(){

}


void AccTranslation::Transform(float fTime){

	static float lasttime = 0;

	if (lasttime == 0){
		lasttime = fTime;
		return;
	}

	float delta_time = fTime - lasttime;

	m_x_speed += delta_time * m_x_acc;
	m_y_speed += delta_time * m_y_acc;

	lasttime = fTime;

	Translation::Transform(fTime);

}


AlphaChange::AlphaChange(int _style, float _period_time) :m_style(_style), m_period_time(_period_time){

}

AlphaChange::~AlphaChange(){

}


void AlphaChange::Init(){
	switch (m_style){
	case ALPHA_APPEAR:
		m_element->SetAlpha(0.0f);
		break;
	case ALPHA_DISAPPEAR:
		m_element->SetAlpha(1.0f);
		break;
	case ALPHA_APPEAR_DISAPPEAR:
		m_element->SetAlpha(0.0f);
		m_increase = 1;
		break;
	default:
		m_element->SetAlpha(1.0f);
		break;
	}

}


void AlphaChange::Transform(float fTime){
	static float lasttime = 0;

	if (lasttime == 0){
		lasttime = fTime;
		return;
	}

	float delta_time = fTime - lasttime;

	float alpha = m_element->GetAlpha();

	switch (m_style){
	case ALPHA_APPEAR:
		if (alpha >= 1.0){
			m_style = 0;
			m_element->SetAlpha(1.0f);
		} else{
			m_element->SetAlpha(alpha + delta_time / m_period_time );
		}
		break;
	case ALPHA_DISAPPEAR:
		if (alpha <= 0.0){
			m_style = 0;
			m_element->SetAlpha(0.0f);
			m_element->Hide();
		} else{
			m_element->SetAlpha(alpha - delta_time / m_period_time);
		}
		break;
	case ALPHA_APPEAR_DISAPPEAR:
		if (alpha >= 1.0){
			m_element->SetAlpha(1.0f);
			m_increase = -1;
		} else if (m_increase == -1 && alpha <= 0){
			m_element->SetAlpha(0.0f);
			m_increase = 1;
		}
		m_element->SetAlpha(alpha + m_increase*(delta_time / m_period_time));
		break;
	default:
		m_element->SetAlpha(1.0f);
		break;
	}


	lasttime = fTime;



}