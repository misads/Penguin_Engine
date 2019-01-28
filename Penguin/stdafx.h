// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
#pragma once

#include "targetver.h"



//#define WIN32_LEAN_AND_MEAN             //  从 Windows 头文件中排除极少使用的信息
// Windows 头文件: 
//#include <afx.h>
#include <windows.h>
//#include <Psapi.h>

// C 运行时头文件
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
//STL头文件
#include <vector>
#include <map>
#include <utility>
#include <queue>
#include <set>


//TODO:  在此处引用程序需要的其他头文件
#include <atlstr.h>
#include "Ini.h"
#include "App.h"



#include "CD2D.h"
#include "CD2DAnimation.h"

#include "Game.h"



//一次性创建的对象
extern CIni	Ini;

extern CD2D D2DC;



extern CGame Game;
extern CApp	APP;





