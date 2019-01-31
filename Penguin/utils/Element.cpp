#include "stdafx.h"
#include "Element.h"


CElement::CElement(){
	m_alphachange.style = 0;
}

CElement::~CElement()
{
}

int CElement::GetDirection(){
	return m_direction;
}
void CElement::SetDirection(Direction _direction){
	m_direction = _direction;
}


fPoint CElement::GetPos(){
	return m_pos;
}
void CElement::SetPos(float _x, float _y){
	m_pos = fPoint(_x, _y);
}

Vector CElement::GetShape(){
	return m_shape;
}
void CElement::SetShape(int _x, int _y){
	m_shape = Vector(_x, _y);
}


float CElement::GetSpeed(){
	return m_speed;
}
void CElement::SetSpeed(float _speed){
	m_speed = _speed;
}

void CElement::SetAlphaChange(int _style, float _period_time){
	m_alphachange.style = _style;
	m_alphachange.period_time = _period_time;
	m_alphachange.previous_time = 0;
	switch (_style){
	case ALPHA_APPEAR:
		m_alpha = 0.0f;
		break;
	case ALPHA_DISAPPEAR:
		m_alpha = 1.0f;
		break;
	case ALPHA_APPEAR_DISAPPEAR:
		m_alpha = 0.0f;
		m_alphachange.increase = 1;
		break;
	case ALPHA_DISAPPEAR_APPEAR:
		m_alpha = 1.0f;
		m_alphachange.increase = -1;
		break;
	default:
		m_alpha = 1.0f;
		break;
	}
}

void CElement::Move(Direction direction, float _pixel){
	if (direction == 1)m_pos = fPoint(m_pos.x, m_pos.y - _pixel);
	if (direction == 2)m_pos = fPoint(m_pos.x, m_pos.y + _pixel);
	if (direction == 3)m_pos = fPoint(m_pos.x - _pixel, m_pos.y);
	if (direction == 4)m_pos = fPoint(m_pos.x + _pixel, m_pos.y);

}

void CElement::SetObject(CD2DObject _object){
	m_object = _object;
	m_type = D2D_MOTION;
}

void CElement::SetObject(CD2DImage _image){
	m_image = _image;
	m_type = D2D_IMAGE;
}

void CElement::SetObject(LPCTSTR sFontName, FLOAT fFontSize,
	CString sText, DWORD rgb, FLOAT _Alpha, bool AlienToRight){
	m_text = D2DTEXT(sFontName, fFontSize,
		sText,rgb,_Alpha, AlienToRight);
	
	m_type = D2D_TEXT;
}

void CElement::SetText(CString sText){
	m_text.sText = sText;
}

void CElement::SetLastTime(float _lasttime){
	m_lastTime = _lasttime;
}

void CElement::SetRenderTarget(ID2D1HwndRenderTarget* pRenderTarget){
	m_renderTarget = pRenderTarget;
}

void CElement::Render(float fTime, FLOAT _alpha){
	if (m_renderTarget == nullptr) throw "renderTarget null error";

	if (!m_visible)return;

	if (m_alphachange.style != 0){
		if (m_alphachange.previous_time == 0){
			m_alphachange.previous_time = fTime;
			return;
		}
		float deltatime = fTime - m_alphachange.previous_time;
		switch (m_alphachange.style){
		case ALPHA_APPEAR:
			if (m_alpha >= 1.0){
				m_alphachange.style = 0;
				_alpha = 1.0f;
			}
			else{
				m_alpha += deltatime / m_alphachange.period_time;
			}
			break;
		case ALPHA_DISAPPEAR:
			if (m_alpha <= 0.0){
				m_alphachange.style = 0;
				_alpha = 0.0f;
				m_visible = false;
			}
			else{
				m_alpha -= deltatime / m_alphachange.period_time;
			}
			break;
		case ALPHA_APPEAR_DISAPPEAR:
			if (m_alpha >= 1.0){
				_alpha = 1.0f;
				m_alphachange.increase = -1;
			}
			else if (m_alphachange.increase == -1 && m_alpha <= 0){
				_alpha = 0.0f;
				m_alphachange.increase = 1;
			}
			m_alpha += m_alphachange.increase * (deltatime / m_alphachange.period_time);
			break;
		case ALPHA_DISAPPEAR_APPEAR:
			if (m_alpha <= 0.0){
				_alpha = 0.0f;
				m_alphachange.increase = 1;
			}
			else if (m_alphachange.increase == 1 && m_alpha >= 1.0){
				_alpha = 1.0f;
				m_alphachange.increase = -1;
			}
			m_alpha += m_alphachange.increase * (deltatime / m_alphachange.period_time);
		default:
			_alpha = 1.0f;
			break;
		}
		m_alphachange.previous_time = fTime;
		_alpha = m_alpha;

	}

	if (m_type == D2D_MOTION){
		m_object.Render(m_renderTarget, fTime, m_pos.x, m_pos.y, m_shape.x, m_shape.y, _alpha);
		return;
	}


	if (m_curTime == 0){
		m_curTime = fTime;
	}
	else{

		if (m_lastTime!=0 && fTime - m_curTime > m_lastTime){

			m_visible = false;
			m_curTime = 0;
		}
	}

	switch (m_type)
	{
	case D2D_TEXT:
		D2DC.DrawTextC(m_text.sFontName, m_text.fFontSize, m_pos.x, m_pos.y, 
			m_pos.x + m_shape.x, m_pos.y + m_shape.y, m_text.sText, m_text.rgb,_alpha, m_text.AlienToRight);
		break;
	case D2D_IMAGE:
		D2DC.DrawBmp(m_image, m_pos.x - m_shape.x * 0.5f, m_pos.y - m_shape.y * 0.5f, m_shape.x, m_shape.y, _alpha);
	default:


		break;
	}
	
}

void CElement::Show(){
	switch (m_type)
	{
	case D2D_MOTION:
		m_object.Reset();
		break;
	default:
		m_visible = true;
		m_curTime = 0;
		break;
	}
}

bool CElement::IsVisible(){
	switch (m_type)
	{
	case D2D_MOTION:
		return m_object.IsVisible();
	default:
		return m_visible;
		break;
	}

}

ID2D1HwndRenderTarget* CElement::m_renderTarget = nullptr;