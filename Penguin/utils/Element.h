#pragma once
#include "Arith.h"
#include "CD2DObject.h"

#define D2D_MOTION 1
#define D2D_IMAGE 2
#define D2D_TEXT 3

#define ALPHA_APPEAR 1
#define ALPHA_DISAPPEAR 2
#define ALPHA_APPEAR_DISAPPEAR 3
#define ALPHA_DISAPPEAR_APPEAR 4

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

struct ALPHA_CHANGE{
	int style;
	float period_time;
	float previous_time;
	int increase;
};
class CElement{
public:
	CElement();
	~CElement();

	int GetDirection();
	void SetDirection(Direction _direction);

	fPoint GetPos();
	void SetPos(float _x, float _y);

	Vector GetShape();
	void SetShape(int _x, int _y);

	float GetSpeed();
	void SetSpeed(float _speed);

	void SetAlphaChange(int _style, float _period_time);

	void Move(Direction direction, float _pixel);

	void SetObject(CD2DObject _object);
	void SetObject(CD2DImage _image);
	void SetObject(LPCTSTR sFontName, FLOAT fFontSize,
		CString sText, DWORD rgb = 0, FLOAT _Alpha = 1.0F, bool AlienToRight = false);

	void SetText(CString sText);

	//持续时间
	void SetLastTime(float _lasttime);

	void SetRenderTarget(ID2D1HwndRenderTarget* pRenderTarget);

	void Render(float fTime,FLOAT _alpha=1.0F);

	void Show();

	bool IsVisible();

private:
	CD2DObject	m_object;
	CD2DImage	m_image;
	D2DTEXT		m_text;
	bool		m_visible;

	float		m_curTime;
	float		m_lastTime;

	int			m_direction;
	fPoint		m_pos;
	Vector		m_shape;
	float		m_alpha;
	float		m_speed;

	int			m_type;
	
	ALPHA_CHANGE m_alphachange;

	static		ID2D1HwndRenderTarget* m_renderTarget;
};

