#include "CD2D.h"


#ifndef _CD2DANIMATION_H
#define _CD2DANIMATION_H

#pragma once

class CD2DAnimation{
public:
	CD2DAnimation(CD2DImage Image, Point nStartPos, Vector vFrameSize, Vector vSplitNum, fVector fDrawSize=fVector(0,0), int nFrameCount = 0, FLOAT alpha = 1.0F,int nCycles=-1);
	CD2DAnimation();
	~CD2DAnimation();
	
	bool InitRes(CD2DImage Image, Point nStartPos, Vector vFrameSize, Vector vSplitNum, fVector fDrawSize = fVector(0, 0), int nFrameCount = 0, FLOAT alpha = 1.0F,int nCycles = -1);

	bool Render(ID2D1HwndRenderTarget* pRenderTarget, float fTime);

	void SetPosition(fPoint fPos);//����λ�� ���ٸ���λ(��Ϊ1000 ��Ϊ562)
	void SetMove(bool bMove, Direction direction = nodirection, FLOAT fSpeed = 100.0f); //�����ƶ� �ٶ��Ƕ��ٸ���λ
	void SetFramePerSecond(int nFPS);//����FPS

	void SetAlpha(FLOAT fAlpha);
	void SetAlphaChange(FLOAT fAlphaChange);

	void SetCycles(int nCycles);



protected:


	//ʵ��λ��= SCREEN_WIDTH/MAX_WIDTH_UNIT*���λ��
	ID2D1Bitmap*	m_pBitmap;//ͼƬ

	bool			m_bActive;


	fPoint		m_fPos;	//λ�� ���ٸ���λ(��Ϊ1000 ��Ϊ562)

	bool			m_bMove;//�Ƿ��ƶ�
	Direction		m_dMoveDirection;//�ƶ�����
	FLOAT		m_fMoveSpeed;//���ٵ�λһ�� �ܵ�λ��Ϊ1000 ��Ϊ562 ʵ��λ��= SCREEN_WIDTH/MAX_WIDTH_UNIT*���λ��

	int			m_nFramePerSecond;//һ�����֡

	float		m_fLastTime;//��һ��ˢ�µ�ʱ��
	fPoint		m_fLastPos;	//��һ��ˢ�µ�λ��
	int			m_nCycles;//ѭ�����ٴ�

	Point			m_nStartPos;//ͼƬ�ϵ���ʼ��
	fVector		m_fDrawSize;//�����
	Vector		m_vFrameSize;//һ֡�Ĵ�С ��λΪ���� 
	Vector		m_vSplitNum;//���г�M*N��ͼƬ
	int			m_nFrameCount;//һ���ж���֡

	FLOAT		m_fAlpha;//͸����
	FLOAT		m_fAlphaChangeEachFrame;//ÿ֡�ı��͸����

	int			m_nCurFrameX;//��ǰ֡x,��0��ʼ
	int			m_nCurFrameY;//��ǰ֡y,��0��ʼ

	bool			nextFrame();

};





#endif
