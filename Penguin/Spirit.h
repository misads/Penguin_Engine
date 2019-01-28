#include "CommonHead.h"

#ifndef _H_SPIRIT_H
#define _H_SPIRIT_H
#pragma once


//基类
class CSpirit{
public:
	CSpirit(void);
	~CSpirit(void);

	//将方向与对应的动画加载到映射m_mMoveAnimation中

#ifndef _D2DRender_
	bool	LoadAnimationRes(Direction direction, CAnimation animation);

	map<Direction, CAnimation>m_mAnimation;
#else
	bool	LoadAnimationRes(Direction direction, CD2DAnimation animation,bool bMove=false);

	map<Direction, CD2DAnimation>m_mMoveAnimation;
	map<Direction, CD2DAnimation>m_mStandAnimation;


	Point GetPosition();
	void SetPosition(Point fPos);

	int	GetFloor();
	void SetFloor(int _floor);

	Direction GetDirection();
	
	bool SetDirection(Direction direction);


	bool	Render(float fTime);
#endif


protected:

	//fPoint			m_fPos;//位置
	int				m_nFloor;

	Point				m_nPos;//整数位置

	Direction			m_direction;//朝向
	float			m_fLastTime;//上次的时间

	//bool				m_bMoving;//是否正在移动
	//Direction			m_direction;//朝向
	bool				m_bActive;//是否存在
	bool				m_bVisible;//是否可见


};







#endif