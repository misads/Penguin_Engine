#ifndef _SERVER_

#include <Windows.h>
#include "Arith.h"
#include "CommonHead.h"

#ifndef _H_ANIMATION_H
#define _H_ANIMATION_H
#pragma once


#ifndef _D2DRender_



class CAnimation{
public:
	//lpResPath����:TEXT("animation/1.bmp")
	CAnimation(LPCTSTR lpResPath, Point nStartPos, Vector vFrameSize, Vector vSplitNum,DWORD dwTransparentColor=-1);
	CAnimation();
	~CAnimation();

	bool Render(HDC hdc, float fTime);
	//bool PickNewDirection(Direction d);

	fPoint		m_fPos;	//λ��

	bool			m_bMove;//�Ƿ��ƶ�
	Direction		m_dMoveDirection;//�ƶ�����
	int			m_nMoveSpeed;//���ٵ�λһ�� �ܵ�λ��Ϊ1000 ��Ϊ562 ʵ��λ��= SCREEN_WIDTH/MAX_WIDTH_UNIT*���λ��

	int			m_nFramePerSecond;//һ�����֡
	

protected:

	
	//ʵ��λ��= SCREEN_WIDTH/MAX_WIDTH_UNIT*���λ��
	HBITMAP		m_hResBitmap;//ͼƬ�ļ�

	float		m_fLastTime;//��һ��ˢ�µ�ʱ��
	fPoint		m_fLastPos;	//��һ��ˢ�µ�λ��

	Point			m_nStartPos;//ͼƬ�ϵ���ʼ��
	Vector		m_vFrameSize;//һ֡�Ĵ�С ��λΪ���� 
	Vector		m_vSplitNum;//���г�M*N��ͼƬ

	DWORD		m_dwTransparentColor;//͸��ɫ
	bool			m_bTransparentBlt;//͸��ͼƬ


	int			m_nCurFrameX;//��ǰ֡x,��0��ʼ
	int			m_nCurFrameY;//��ǰ֡y,��0��ʼ
	
	bool			nextFrame();
};

#endif

#endif
#endif