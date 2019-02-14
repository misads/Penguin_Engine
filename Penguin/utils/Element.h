#pragma once
#include "Arith.h"
#include "CD2DObject.h"
#include "Transforms.h"

#define D2D_MOTION 1
#define D2D_IMAGE 2
#define D2D_TEXT 3



extern CD2D D2DC;

struct D2DTEXT{
	D2DTEXT(){}
	D2DTEXT(LPCTSTR _sFontName, FLOAT _fFontSize,
	CString _sText, DWORD _rgb, FLOAT _Alpha, bool _AlienToRight){
		sFontName = _sFontName;
		fFontSize = _fFontSize;
		sText = _sText;
		rgb = _rgb;
		Alpha = _Alpha;
		AlienToRight = _AlienToRight;

	}
	LPCTSTR sFontName;
	FLOAT fFontSize;
	FLOAT left;
	FLOAT top;
	FLOAT right;
	FLOAT bottom;
	CString sText;
	DWORD rgb;
	FLOAT Alpha;
	bool AlienToRight;
};

class CElement{
public:
	CElement();
	~CElement();

	int GetDirection();
	void SetDirection(Direction _direction);

	Point<float> GetPos();
	void SetPos(float _x, float _y);

	Shape<int> GetShape();
	void SetShape(int _x, int _y);

	float GetSpeed();
	void SetSpeed(float _speed);

	//加速度
	float GetAcceleration();
	//加速度
	void SetAcceleration(Direction _direction, float _acceleration);

	float GetAlpha();
	void SetAlpha(float _alpha);

	void Move(Direction _direction, float _pixel);
	void Move(float _x, float _y);

	
	void AddTranform(BaseTransform*);

	void SetObject(CD2DObject _object);
	void SetObject(CD2DImage _image);
	void SetObject(LPCTSTR sFontName, FLOAT fFontSize,
		CString sText, DWORD rgb = 0, FLOAT _Alpha = 1.0F, bool AlienToRight = false);

	void SetText(CString sText);

	//持续时间
	void SetLastTime(float _lasttime);

	void SetRenderTarget(ID2D1HwndRenderTarget* pRenderTarget);

	void Render(float fTime);

	void Hide();
	void Show();

	bool IsVisible();

private:
	CD2DObject		m_object;
	CD2DImage		m_image;
	D2DTEXT			m_text;
	bool			m_visible;

	float			m_curTime;
	float			m_lastTime;

	Direction		m_direction;
	Point<float>m_pos;
	Shape<int>		m_shape;
	float			m_alpha;
	
	float			m_x_speed;
	float			m_y_speed;


	Direction		m_acc_direction;
	float			m_acc_speed;

	int				m_type;

	static			ID2D1HwndRenderTarget* m_renderTarget;

	/*
	void			Move(float fTime);
	void			Accelerate(float fTime);
*/
	vector<BaseTransform*>	m_transforms;
};

