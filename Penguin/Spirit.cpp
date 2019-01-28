#include"stdafx.h"
#include "Spirit.h"

CSpirit::CSpirit(){


}
CSpirit::~CSpirit(){


}

#ifndef _D2DRender_
bool	CSpirit::LoadAnimationRes(Direction direction, CAnimation animation){



	return true;
}
#else

bool CSpirit::LoadAnimationRes(Direction direction, CD2DAnimation animation, bool bMove){
	if (bMove){//�ƶ��Ķ���
		m_mMoveAnimation.insert(pair<Direction, CD2DAnimation>(direction, animation));
	}
	else{//��ֹ��ͼ����
		m_mStandAnimation.insert(pair<Direction, CD2DAnimation>(direction, animation));
	}
	return true;
}
#endif


Point CSpirit::GetPosition(){
	return m_nPos;
}

void CSpirit::SetPosition(Point fPos){
	m_nPos = fPos;

}

int	CSpirit::GetFloor(){

	return m_nFloor;

}

void CSpirit::SetFloor(int _floor){
	m_nFloor = _floor;

}




Direction CSpirit::GetDirection(){
	return m_direction;
}


bool CSpirit::SetDirection(Direction direction){
	m_direction = direction;
	return true;
}

bool	CSpirit::Render(float fTime){
	return true;
}