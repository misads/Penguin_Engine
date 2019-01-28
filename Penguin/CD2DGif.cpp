#include "stdafx.h"
#include "CD2DGif.h"

CD2DGif::CD2DGif(){
	m_nFrameNow = -1;
	m_nFPS = DEFAULT_FPS;
	m_nCycles = 0;
}

CD2DGif::CD2DGif(int nFPS){
	m_nFPS = nFPS;
	m_nFrameNow = -1;
	m_nCycles = 0;
}


CD2DGif::~CD2DGif(){

}

bool CD2DGif::AddImage(CD2DImage Image, Vector vSize){
	GifFrame gBuff;
	gBuff.pBitmap = Image.pBitMap();
	gBuff.vSize = vSize;
	m_vGifFrame.push_back(gBuff);
	return true;
}

bool CD2DGif::Render(ID2D1HwndRenderTarget* pRenderTarget, float fTime, fPoint fCentrePos, fVector fSize, FLOAT fAlpha){

	if (m_nFrameNow == -1) return false;

	if (m_fLastTime == 0){
		m_fLastTime = fTime;
		return false;
	}

	D2D1_RECT_F drawRect = { fCentrePos.x - fSize.x / 2.0f, fCentrePos.y - fSize.y / 2.0f, fCentrePos.x + fSize.x / 2.0f, fCentrePos.y + fSize.y / 2.0f};


	D2D1_RECT_F origRect = {0, 0, m_vGifFrame[m_nFrameNow].vSize.x, m_vGifFrame[m_nFrameNow].vSize.y};


	pRenderTarget->DrawBitmap(m_vGifFrame[m_nFrameNow].pBitmap, drawRect, fAlpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, origRect);


	float fSecondPerFrame = 1 / (m_nFPS*1.0f);
	if (fTime - m_fLastTime >= fSecondPerFrame){
		nextFrame();
		m_fLastTime = fTime;
	}

	return true;
}

bool CD2DGif::Reset(){
	m_nFrameNow = 0;
	return true;
}

bool CD2DGif::Disable(){
	m_nFrameNow = -1;
	return true;
}

void CD2DGif::SetFPS(int nFPS){//ÉèÖÃFPS

	m_nFPS = nFPS;
}
void CD2DGif::SetCycles(int nCycles){

	m_nCycles = nCycles;
	
}

void CD2DGif::SetPosition(Point Pos){
	m_nPos = Pos;

}
Point CD2DGif::GetPosition(){
	return m_nPos;
}


bool	CD2DGif::nextFrame(){
	m_nFrameNow++;

	if (m_nFrameNow > m_vGifFrame.size() - 1){ 
		if (m_nCycles > 0){
			m_nFrameNow = -1;
		}
		else if (m_nCycles == 0){
			m_nFrameNow = -1;

		}
		else if (m_nCycles == -1){
			m_nFrameNow = 0;
		}
		 
	}

	return true;

}