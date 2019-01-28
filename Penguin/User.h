#include "CommonHead.h"
#include "CommonHead.h"

#ifndef _H_USER_H
#define _H_USER_H
#pragma once

#define MAX_USER_NAME 30

//»ùÀà
class CUser{
public:
	CUser(void);
	~CUser(void);

protected:

	long				m_Id;
	WCHAR			m_UserName[MAX_USER_NAME];
	int				m_nLevel;
	int				m_nExp;


	vector<GOODS>	m_vGoods;

};







#endif