// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
#pragma once

#include "targetver.h"



//#define WIN32_LEAN_AND_MEAN             //  �� Windows ͷ�ļ����ų�����ʹ�õ���Ϣ
// Windows ͷ�ļ�: 
//#include <afx.h>
#include <windows.h>
//#include <Psapi.h>

// C ����ʱͷ�ļ�
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
//STLͷ�ļ�
#include <vector>
#include <map>
#include <utility>
#include <queue>
#include <set>


//TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�
#include <atlstr.h>
#include "Ini.h"
#include "App.h"



#include "CD2D.h"
#include "CD2DAnimation.h"

#include "Game.h"



//һ���Դ����Ķ���
extern CIni	Ini;

extern CD2D D2DC;



extern CGame Game;
extern CApp	APP;





