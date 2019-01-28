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
	//lpResPath范例:TEXT("animation/1.bmp")
	CAnimation(LPCTSTR lpResPath, Point nStartPos, Vector vFrameSize, Vector vSplitNum,DWORD dwTransparentColor=-1);
	CAnimation();
	~CAnimation();

	bool Render(HDC hdc, float fTime);
	//bool PickNewDirection(Direction d);

	fPoint		m_fPos;	//位置

	bool			m_bMove;//是否移动
	Direction		m_dMoveDirection;//移动方向
	int			m_nMoveSpeed;//多少单位一秒 总单位长为1000 高为562 实际位置= SCREEN_WIDTH/MAX_WIDTH_UNIT*相对位置

	int			m_nFramePerSecond;//一秒多少帧
	

protected:

	
	//实际位置= SCREEN_WIDTH/MAX_WIDTH_UNIT*相对位置
	HBITMAP		m_hResBitmap;//图片文件

	float		m_fLastTime;//上一次刷新的时间
	fPoint		m_fLastPos;	//上一次刷新的位置

	Point			m_nStartPos;//图片上的起始点
	Vector		m_vFrameSize;//一帧的大小 单位为像素 
	Vector		m_vSplitNum;//共有成M*N张图片

	DWORD		m_dwTransparentColor;//透明色
	bool			m_bTransparentBlt;//透明图片


	int			m_nCurFrameX;//当前帧x,从0开始
	int			m_nCurFrameY;//当前帧y,从0开始
	
	bool			nextFrame();
};

#endif

#endif
#endif