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

	void SetPosition(fPoint fPos);//设置位置 多少个单位(长为1000 高为562)
	void SetMove(bool bMove, Direction direction = nodirection, FLOAT fSpeed = 100.0f); //设置移动 速度是多少个单位
	void SetFramePerSecond(int nFPS);//设置FPS

	void SetAlpha(FLOAT fAlpha);
	void SetAlphaChange(FLOAT fAlphaChange);

	void SetCycles(int nCycles);



protected:


	//实际位置= SCREEN_WIDTH/MAX_WIDTH_UNIT*相对位置
	ID2D1Bitmap*	m_pBitmap;//图片

	bool			m_bActive;


	fPoint		m_fPos;	//位置 多少个单位(长为1000 高为562)

	bool			m_bMove;//是否移动
	Direction		m_dMoveDirection;//移动方向
	FLOAT		m_fMoveSpeed;//多少单位一秒 总单位长为1000 高为562 实际位置= SCREEN_WIDTH/MAX_WIDTH_UNIT*相对位置

	int			m_nFramePerSecond;//一秒多少帧

	float		m_fLastTime;//上一次刷新的时间
	fPoint		m_fLastPos;	//上一次刷新的位置
	int			m_nCycles;//循环多少次

	Point			m_nStartPos;//图片上的起始点
	fVector		m_fDrawSize;//画多大
	Vector		m_vFrameSize;//一帧的大小 单位为像素 
	Vector		m_vSplitNum;//共切成M*N张图片
	int			m_nFrameCount;//一共有多少帧

	FLOAT		m_fAlpha;//透明度
	FLOAT		m_fAlphaChangeEachFrame;//每帧改变的透明度

	int			m_nCurFrameX;//当前帧x,从0开始
	int			m_nCurFrameY;//当前帧y,从0开始

	bool			nextFrame();

};





#endif
