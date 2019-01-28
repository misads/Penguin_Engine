#include"Arith.h"
#include <atlstr.h>
#include <vector>
#include <set>


#ifndef _H_COMMONHEAD_H
#define _H_COMMONHEAD_H
#pragma once

using namespace std;


//条件编译
//#define _DEBUG_  //调试模式
#define DBG
//#define _SERVER_ 服务器模式


#define _D2DRender_ //使用D2D渲染

#ifdef _DEBUG_
#include "Debug.h"
#endif

#ifndef _SERVER_
#define _CLIENT_
#endif

#ifndef _D2DRender_
#define _GDIRender_
#endif

//宏定义的常量
#define INF -1 //无穷大
#define MAX_STRING_LENGTH 260
#define MAX_DATA_LENGTH 200
//#define SCREEN_WIDTH 1366//分辨率 无论是否全屏都一样
//#define SCREEN_HEIGHT 768//分辨率 无论是否全屏都一样

#define MAX_WIDTH_UNIT 1366  //最大宽度单位 实际位置= SCREEN_WIDTH/MAX_WIDTH_UNIT*相对位置
#define MAX_HEIGHT_UNIT 768 //最大高度单位 实际位置= SCREEN_HEIGHT/MAX_HEIGHT_UNIT*相对位置

//#define MAX_WIDTH_UNIT 1000  //最大宽度单位 实际位置= SCREEN_WIDTH/MAX_WIDTH_UNIT*相对位置
//#define MAX_HEIGHT_UNIT 562 //最大高度单位 实际位置= SCREEN_HEIGHT/MAX_HEIGHT_UNIT*相对位置


//宏定义的函数
#define SCHEDULE(fPeriodSecond,DoWhat) if (fTime != 0){static float fLastTime = 0;	if (fTime - fLastTime < fPeriodSecond){	DoWhat; return true;}	else fLastTime = fTime;}
#define SCHEDULE2(fPeriodSecond,DoWhat) if (fTime != 0){static float fLastTime2 = 0;	if (fTime - fLastTime2 < fPeriodSecond){	DoWhat; return true;}	else fLastTime2 = fTime;}







#endif