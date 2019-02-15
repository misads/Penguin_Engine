#include "stdafx.h"
#include "CD2DImage.h"
#include "CD2DObject.h"

CD2DObject::CD2DObject(){
	m_framenow = -1;
	m_fps = DEFAULT_FPS;
	m_cycles = 0;
	m_cyclenow = 0;
}

CD2DObject::CD2DObject(int _fps){
	m_fps = _fps;
	m_framenow = -1;
	m_cycles = 0;
	m_cyclenow = 0;
}


CD2DObject::~CD2DObject(){

}

bool CD2DObject::AddImage(CD2DImage _image, Shape<int> _shape){
	D2DFrame gBuff;
	gBuff.pBitmap = _image.GetBitMap();
	gBuff.shape = _shape;
	m_frames.push_back(gBuff);
	return true;
}

bool CD2DObject::Render(ID2D1HwndRenderTarget* pRenderTarget, float fTime, float centre_x, float centre_y, int _width, int _height, FLOAT _alpha){

	if (m_framenow == -1) return false;

	if (m_lastTime == 0){
		m_lastTime = fTime;
		return false;
	}
	
	D2D1_RECT_F drawRect = { centre_x - _width / 2.0f, centre_y - _height / 2.0f, centre_x + _width / 2.0f, centre_y + _height / 2.0f };


	D2D1_RECT_F origRect = { 0, 0, m_frames[m_framenow].shape.width, m_frames[m_framenow].shape.height };


	pRenderTarget->DrawBitmap(m_frames[m_framenow].pBitmap, drawRect, _alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, origRect);


	float fSecondPerFrame = 1 / (m_fps*1.0f);
	if (fTime - m_lastTime >= fSecondPerFrame){
		nextFrame();
		m_lastTime = fTime;
	}

	return true;
}

bool CD2DObject::Reset(){
	m_framenow = 0;
	m_cyclenow = 0;
	return true;
}

bool CD2DObject::Disable(){
	m_framenow = -1;
	return true;
}

bool CD2DObject::IsVisible(){
	return !(m_framenow == -1);
}

void CD2DObject::SetFps(int _fps){//ÉèÖÃFPS

	m_fps = _fps;
}
void CD2DObject::SetCycles(int _cycles){

	m_cycles = _cycles;
	
}


bool	CD2DObject::nextFrame(){
	m_framenow++;

	if (m_framenow > m_frames.size() - 1){ 
	
		if (m_cycles == -1){
			m_framenow = 0;
		}
		else if (m_cycles - m_cyclenow <= 1){
			m_framenow = -1;
			m_cyclenow = m_cycles;
		}
		else{
			m_framenow = 0;
			m_cyclenow += 1;

		}
		 
	}

	return true;

}