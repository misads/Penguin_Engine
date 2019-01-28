#include "stdafx.h"
#ifdef _D2DRender_
#ifndef _SERVER_

#include "CD2DAnimation.h"

//#define SCREEN_WIDTH 1000//分辨率 无论是否全屏都一样
//#define SCREEN_HEIGHT 562//分辨率 无论是否全屏都一样

//#define MAX_WIDTH_UNIT 1000  //最大宽度单位 实际位置= SCREEN_WIDTH/MAX_WIDTH_UNIT*相对位置
//#define MAX_HEIGHT_UNIT 562 //最大高度单位 实际位置= SCREEN_HEIGHT/MAX_HEIGHT_UNIT*相对位置
#pragma warning (disable: 4244) 


//lpResPath范例:TEXT("animation/1.bmp")
CD2DAnimation::CD2DAnimation(
	CD2DImage Image, Point nStartPos,
	Vector vFrameSize, Vector vSplitNum, fVector fDrawSize,
	int nFrameCount, FLOAT alpha, int nCycles) :
	m_pBitmap(Image.pBitMap()), m_nStartPos(nStartPos),
	m_vFrameSize(vFrameSize), m_vSplitNum(vSplitNum), m_fDrawSize(fDrawSize),
	m_nFrameCount(nFrameCount), m_fAlpha(alpha), 
	m_nCycles(nCycles),m_fLastTime(0),m_bActive(true){

	//m_hResBitmap = GDI.LoadBmpFile(TEXT("animation/1.bmp"));
	if (fDrawSize.x == 0)m_fDrawSize = fVector((float)vFrameSize.x, (float)vFrameSize.y);

	if (!nFrameCount) m_nFrameCount = vSplitNum.x * vSplitNum.y;
	m_nCurFrameX = 0; m_nCurFrameY = 0;

	m_bMove = false;
	m_nFramePerSecond = 20;

}

CD2DAnimation::CD2DAnimation(){
	
	m_bMove = false;

}

bool CD2DAnimation::InitRes(
	CD2DImage Image, Point nStartPos,
	Vector vFrameSize, Vector vSplitNum, fVector fDrawSize,
	int nFrameCount, FLOAT alpha, int nCycles) {

	m_pBitmap = Image.pBitMap();
	m_nStartPos = (nStartPos);
	m_vFrameSize = (vFrameSize);
	m_vSplitNum = (vSplitNum);
	m_fDrawSize = fDrawSize;
	m_fAlpha = (alpha);
	m_nCycles = nCycles;
	m_fLastTime = 0;
	m_bActive = true;

	//m_hResBitmap = GDI.LoadBmpFile(TEXT("animation/1.bmp"));
	if (fDrawSize.x == 0)m_fDrawSize = fVector((float)vFrameSize.x, (float)vFrameSize.y);
	m_nFrameCount = nFrameCount;
	if (!nFrameCount) m_nFrameCount = vSplitNum.x * vSplitNum.y;
	m_nCurFrameX = 0; m_nCurFrameY = 0;
	return true;
}

CD2DAnimation::~CD2DAnimation(){
	//if (m_hResBitmap)DeleteObject(m_hResBitmap);
	//SAFE_RELEASE(m_pBitmap);
	
}

bool CD2DAnimation::Render(ID2D1HwndRenderTarget* pRenderTarget, float fTime){
	if (!m_bActive)return false;
	if (m_fLastTime == 0){
		m_fLastTime = fTime;
		m_fLastPos = m_fPos;
		return false;
	}
	//fVector fMoveUnit = fPoint(Game.m_gameConfig.SCREEN_WIDTH / (MAX_WIDTH_UNIT *1.0f),
	//	Game.m_gameConfig.SCREEN_HEIGHT / (MAX_HEIGHT_UNIT*1.0f));
	if (m_bMove){


		switch (m_dMoveDirection)
		{
		case up:
			break;
		case down:
			break;
		case left:
			break;
		case right:
			m_fPos = fPoint(m_fLastPos.x + (m_fMoveSpeed) *(fTime - m_fLastTime), m_fLastPos.y);
			break;
		default:
			break;
		}
	}

		
	//GDI.DrawTransparentBmp(hdc, m_hResBitmap, (int)m_fPos.fx, (int)m_fPos.fy,
	//m_vFrameSize.nx, m_vFrameSize.ny, 
	//m_nStartPos.nx + m_vFrameSize.nx * m_nCurFrameX,
	//m_nStartPos.ny + m_vFrameSize.ny * m_nCurFrameY, m_dwTransparentColor);


	
	D2D1_RECT_F drawRect = { m_fPos.x * Game.GetUnitScale().x, m_fPos.y * Game.GetUnitScale().y,
		(m_fPos.x + m_fDrawSize.x)* Game.GetUnitScale().x, (m_fPos.y + m_fDrawSize.y)* Game.GetUnitScale().y };
	int nSrcX = m_nStartPos.x + m_vFrameSize.x * m_nCurFrameX;
	int nSrcY = m_nStartPos.y + m_vFrameSize.y * m_nCurFrameY;
	D2D1_RECT_F origRect = { nSrcX, nSrcY, nSrcX + m_vFrameSize.x, nSrcY + m_vFrameSize.y };

	pRenderTarget->DrawBitmap(m_pBitmap, drawRect, m_fAlpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, origRect);


	float fSecondPerFrame = 1 / (m_nFramePerSecond*1.0f);
	if (fTime - m_fLastTime >= fSecondPerFrame){
		nextFrame();
		m_fLastTime = fTime;
		m_fLastPos = m_fPos;
	}



	return true;
}

bool CD2DAnimation::nextFrame(){


	if (m_nCurFrameY*m_vSplitNum.x + m_nCurFrameX >= m_nFrameCount-1){
		m_nCurFrameX = 0;
		m_nCurFrameY = 0;
		if (m_nCycles>0) m_nCycles--;
		if (!m_nCycles) m_bActive = false;
		return true;
	}
	if (m_nCurFrameX >= m_vSplitNum.x - 1){
		if (m_nCurFrameY >= m_vSplitNum.y - 1){
			m_nCurFrameX = 0;
			m_nCurFrameY = 0;
			if (m_nCycles>0) m_nCycles--;
			if (!m_nCycles)m_bActive = false;
		}
		else{
			m_nCurFrameY++;
			m_nCurFrameX = 0;
			if (m_fAlphaChangeEachFrame) m_fAlpha += m_fAlphaChangeEachFrame;
			if (m_fAlpha > 1)m_fAlpha = 0;
			if (m_fAlpha < 0)m_fAlpha = 1;
		}
	}
	else{
		m_nCurFrameX++;
		if (m_fAlphaChangeEachFrame) m_fAlpha += m_fAlphaChangeEachFrame;
		if (m_fAlpha > 1)m_fAlpha = 0;
		if (m_fAlpha < 0)m_fAlpha = 1;
	}


	return true;

}

void CD2DAnimation::SetPosition(fPoint fPos){
	m_fPos = fPos;
}

void CD2DAnimation::SetMove(bool bMove, Direction direction , FLOAT fSpeed){
	m_bMove = bMove;
	m_dMoveDirection = direction; 
	m_fMoveSpeed = fSpeed;
}

void CD2DAnimation::SetFramePerSecond(int nFPS){
	m_nFramePerSecond = nFPS;
}

void CD2DAnimation::SetAlpha(FLOAT fAlpha){
	m_fAlpha = fAlpha;

}

void CD2DAnimation::SetAlphaChange(FLOAT fAlphaChange){
	m_fAlphaChangeEachFrame = fAlphaChange;

}

void CD2DAnimation::SetCycles(int nCycles){
	m_nCycles = nCycles;
	if (nCycles)m_bActive = true;
}

#endif

#endif
