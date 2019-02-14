#include "stdafx.h"
#include "Element.h"


CElement::CElement(){
	m_alpha = 1.0f;
	m_acc_speed = 0;

}

CElement::~CElement(){
	for (int i = 0; i < m_transforms.size(); i++){
		delete m_transforms[i];
	}
}

int CElement::GetDirection(){
	return m_direction;
}
void CElement::SetDirection(Direction _direction){
	m_direction = _direction;
}


Point<float> CElement::GetPos(){
	return m_pos;
}
void CElement::SetPos(float _x, float _y){
	m_pos = Point<float>(_x, _y);
}

Shape<int> CElement::GetShape(){
	return m_shape;
}
void CElement::SetShape(int _x, int _y){
	m_shape = Shape<int>(_x, _y);
}


float CElement::GetSpeed(){
	return 0;
}
void CElement::SetSpeed(float _speed){
	
}

float CElement::GetAcceleration(){
	return m_acc_speed;
}

void CElement::SetAcceleration(Direction _direction, float _speed){
	m_acc_direction = _direction;
	m_acc_speed = _speed;
}

float CElement::GetAlpha(){
	return m_alpha;
}

void CElement::SetAlpha(float _alpha){
	m_alpha = _alpha;

}

void CElement::Move(Direction _direction, float _pixel){
	if (_direction == 1)m_pos = Point<float>(m_pos.x, m_pos.y - _pixel);
	if (_direction == 2)m_pos = Point<float>(m_pos.x, m_pos.y + _pixel);
	if (_direction == 3)m_pos = Point<float>(m_pos.x - _pixel, m_pos.y);
	if (_direction == 4)m_pos = Point<float>(m_pos.x + _pixel, m_pos.y);

}

void CElement::Move(float _x, float _y){

	m_pos = Point<float>(m_pos.x + _x, m_pos.y + _y);

}





void CElement::AddTranform(BaseTransform* _transform){
	_transform->SetElement(this);
	_transform->Init();
	m_transforms.push_back(_transform);
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

void CElement::Render(float fTime){
	if (m_renderTarget == nullptr) throw "renderTarget null error";

	if (!m_visible)return;

	for (int i = 0; i < m_transforms.size(); i++){
		m_transforms[i]->Transform(fTime);
	}



	if (m_type == D2D_MOTION){
		m_object.Render(m_renderTarget, fTime, m_pos.x, m_pos.y, m_shape.width, m_shape.height, m_alpha);
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
			m_pos.x + m_shape.width, m_pos.y + m_shape.height, m_text.sText, m_text.rgb,m_alpha, m_text.AlienToRight);
		break;
	case D2D_IMAGE:
		D2DC.DrawBmp(m_image, m_pos.x - m_shape.width * 0.5f, m_pos.y - m_shape.height * 0.5f, m_shape.width, m_shape.height, m_alpha);
	default:


		break;
	}
	
}

void CElement::Hide(){
	m_visible = false;
}

void CElement::Show(){
	switch (m_type)
	{
	case D2D_MOTION:
		m_object.Reset();
		m_visible = true;
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
/*
void CElement::Move(float fTime){
	static float previous_time = 0;
	if (previous_time == 0){
		previous_time = fTime;
		return;
	}
	float delta_time = fTime - previous_time;
	Move(m_direction, m_speed * delta_time);
	previous_time = fTime;


}

void CElement::Accelerate(float fTime){
	static float previous_time = 0;
	if (previous_time == 0){
		previous_time = fTime;
		return;
	}
	float delta_time = fTime - previous_time;

	Move(m_direction, m_speed * delta_time);
	previous_time = fTime;


}*/