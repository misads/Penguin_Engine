#include "CommonHead.h"

#ifndef _H_SPIRIT_H
#define _H_SPIRIT_H
#pragma once


//����
class CSpirit{
public:
	CSpirit(void);
	~CSpirit(void);

	//���������Ӧ�Ķ������ص�ӳ��m_mMoveAnimation��

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

	//fPoint			m_fPos;//λ��
	int				m_nFloor;

	Point				m_nPos;//����λ��

	Direction			m_direction;//����
	float			m_fLastTime;//�ϴε�ʱ��

	//bool				m_bMoving;//�Ƿ������ƶ�
	//Direction			m_direction;//����
	bool				m_bActive;//�Ƿ����
	bool				m_bVisible;//�Ƿ�ɼ�


};







#endif