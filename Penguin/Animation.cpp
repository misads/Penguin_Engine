#include "stdafx.h"

#ifndef _D2DRender_



#include "Animation.h"
#include "Game.h"


//lpResPath·¶Àý:TEXT("animation/1.bmp")
CAnimation::CAnimation(
	LPCTSTR lpResPath, 
	Point nStartPos, 
	Vector vFrameSize, 
	Vector vSplitNum, DWORD dwTransparentColor) :m_nStartPos(nStartPos), m_vFrameSize(vFrameSize), m_vSplitNum(vSplitNum), m_dwTransparentColor(dwTransparentColor), m_fLastTime(0){
	
	//m_hResBitmap = GDI.LoadBmpFile(TEXT("animation/1.bmp"));
	m_hResBitmap = GDI.LoadBmpFile(lpResPath);
	if (dwTransparentColor == -1) m_bTransparentBlt = false; else m_bTransparentBlt = true;
	m_nCurFrameX = 0; m_nCurFrameY = 0;
}

CAnimation::CAnimation(){


}

CAnimation::~CAnimation(){
	if (m_hResBitmap)DeleteObject(m_hResBitmap);
}

bool CAnimation::Render(HDC hdc,float fTime){
	if (m_fLastTime == 0 ){
		m_fLastTime = fTime;
		m_fLastPos = m_fPos;
		return false;
	}
	if (m_bMove){
		fVector fMoveUnit = fPoint(SCREEN_WIDTH / (MAX_WIDTH_UNIT *1.0f),
			SCREEN_HEIGHT / (MAX_HEIGHT_UNIT*1.0f));

		switch (m_dMoveDirection)
		{
		case up:
			break;
		case down:
			break;
		case left:
			break;
		case right:
			m_fPos = fPoint(m_fLastPos.fx + (m_nMoveSpeed *fMoveUnit.fx) *(fTime - m_fLastTime), m_fLastPos.fy);
			break;
		default:
			break;
		}
	}

	float fSecondPerFrame = 1 / (m_nFramePerSecond*1.0f);
	if (fTime - m_fLastTime >= fSecondPerFrame){
		nextFrame();
		m_fLastTime = fTime;
		m_fLastPos = m_fPos;
	}

	if (m_bTransparentBlt){
		//if (!Game.m_bEmployHardwareRender)
			GDI.DrawTransparentBmp(hdc, m_hResBitmap, (int)m_fPos.fx, (int)m_fPos.fy,
				m_vFrameSize.nx, m_vFrameSize.ny, m_nStartPos.nx+ m_vFrameSize.nx * m_nCurFrameX,
				m_nStartPos.ny + m_vFrameSize.ny * m_nCurFrameY, m_dwTransparentColor);
			
	}
	else{
		//if (!Game.m_bEmployHardwareRender);// GDI.DrawBmp();

	}


	return true;
}

bool CAnimation::nextFrame(){
	if (m_nCurFrameX >= m_vSplitNum.nx - 1){
		if (m_nCurFrameY >= m_vSplitNum.ny - 1){
			m_nCurFrameX=0;
			m_nCurFrameY=0;
		}
		else{
			m_nCurFrameY++;
		}
	}
	else{
		m_nCurFrameX++;
	}

	
	return true;

}



#endif