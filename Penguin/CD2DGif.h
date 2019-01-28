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
	
	bool Disable(); //��ʧ

	void SetFPS(int nFPS);//����FPS

	void SetCycles(int nCycles);

	void SetPosition(Point Pos);

	Point GetPosition();

protected:


	//ʵ��λ��= SCREEN_WIDTH/MAX_WIDTH_UNIT*���λ��
	vector<GifFrame>	m_vGifFrame;//ͼƬ

	//bool			m_bActive;

	Point			m_nPos;

	int			m_nFPS;//һ�����֡

	float		m_fLastTime;//��һ��ˢ�µ�ʱ��
	fPoint		m_fLastPos;	//��һ��ˢ�µ�λ��
	int			m_nCycles;//ѭ�����ٴ�

	Vector		m_vFrameSize;//һ֡�Ĵ�С ��λΪ���� 

	int			m_nFrameNow;//�����ǵڼ�֡ ������Ϊ-1
	
	FLOAT		m_fAlphaChangeEachFrame;//ÿ֡�ı��͸����

	bool			nextFrame();

};


#endif
#endif
