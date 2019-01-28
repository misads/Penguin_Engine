#include "CommonHead.h"

#ifdef _D2DRender_

#include "CD2D.h"


#ifndef _CD2DGIF_H
#define _CD2DGIF_H

#pragma once

#define DEFAULT_FPS 10


struct GifFrame{
	ID2D1Bitmap* pBitmap;
	Vector vSize;
};

class CD2DGif{
public:

	CD2DGif();
	CD2DGif(int nFPS);
	~CD2DGif();

	bool AddImage(CD2DImage Image, Vector vSize);

	bool Render(ID2D1HwndRenderTarget* pRenderTarget, float fTime, fPoint fCentrePos, fVector fSize, FLOAT fAlpha = 1.0F);

	bool Reset();
	
	bool Disable(); //消失

	void SetFPS(int nFPS);//设置FPS

	void SetCycles(int nCycles);

	void SetPosition(Point Pos);

	Point GetPosition();

protected:


	//实际位置= SCREEN_WIDTH/MAX_WIDTH_UNIT*相对位置
	vector<GifFrame>	m_vGifFrame;//图片

	//bool			m_bActive;

	Point			m_nPos;

	int			m_nFPS;//一秒多少帧

	float		m_fLastTime;//上一次刷新的时间
	fPoint		m_fLastPos;	//上一次刷新的位置
	int			m_nCycles;//循环多少次

	Vector		m_vFrameSize;//一帧的大小 单位为像素 

	int			m_nFrameNow;//现在是第几帧 结束了为-1
	
	FLOAT		m_fAlphaChangeEachFrame;//每帧改变的透明度

	bool			nextFrame();

};


#endif
#endif
