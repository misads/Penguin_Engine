#pragma once

#define DIRECTION_SPEED 1
#define XY_SPEED 2

#define sqrt2 1.41421356
#define half_sqrt2 0.707100678

#define ALPHA_APPEAR 1
#define ALPHA_DISAPPEAR 2
#define ALPHA_APPEAR_DISAPPEAR 3

class CElement; //前向声明

class BaseTransform{
public:
	BaseTransform();
	~BaseTransform();

	void SetElement(CElement* e);

	virtual void Init() = 0;
	virtual void Transform(float fTime) = 0;

protected:
	CElement*	m_element;

};


//平移
class Translation :public BaseTransform{
public:
	Translation(Direction d = Null, float speed = 0);
	Translation(float speed_x, float speed_y);
	~Translation();

	void Init();
	void Transform(float fTime);

protected:
	float	m_x_speed;
	float	m_y_speed;

	static float	m_x[9];
	static float	m_y[9];

};

class AccTranslation :public Translation{
public:
	AccTranslation(Direction _d = Null, float _acc = 0, float _speed = 0);
	AccTranslation(float acc_x, float acc_y, float speed_x, float speed_y);
	~AccTranslation();

	void Transform(float fTime);

private:
	float	m_x_acc;
	float	m_y_acc;

};


class AlphaChange : public BaseTransform{
public:
	/*
	参数
	ALPHA_APPEAR 1
	ALPHA_DISAPPEAR 2
	ALPHA_APPEAR_DISAPPEAR 3
	*/
	AlphaChange(int _style, float _period_time = 1.0f);
	~AlphaChange();

	void Init();
	void Transform(float fTime);

private:
	int m_style; 
	float m_period_time;
	int m_increase;
};


