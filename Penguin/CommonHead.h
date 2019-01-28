#include"Arith.h"
#include <atlstr.h>
#include <vector>
#include <set>


#ifndef _H_COMMONHEAD_H
#define _H_COMMONHEAD_H
#pragma once

using namespace std;


//��������
//#define _DEBUG_  //����ģʽ
#define DBG
//#define _SERVER_ ������ģʽ


#define _D2DRender_ //ʹ��D2D��Ⱦ

#ifdef _DEBUG_
#include "Debug.h"
#endif

#ifndef _SERVER_
#define _CLIENT_
#endif

#ifndef _D2DRender_
#define _GDIRender_
#endif

//�궨��ĳ���
#define INF -1 //�����
#define MAX_STRING_LENGTH 260
#define MAX_DATA_LENGTH 200
//#define SCREEN_WIDTH 1366//�ֱ��� �����Ƿ�ȫ����һ��
//#define SCREEN_HEIGHT 768//�ֱ��� �����Ƿ�ȫ����һ��

#define MAX_WIDTH_UNIT 1366  //����ȵ�λ ʵ��λ��= SCREEN_WIDTH/MAX_WIDTH_UNIT*���λ��
#define MAX_HEIGHT_UNIT 768 //���߶ȵ�λ ʵ��λ��= SCREEN_HEIGHT/MAX_HEIGHT_UNIT*���λ��

//#define MAX_WIDTH_UNIT 1000  //����ȵ�λ ʵ��λ��= SCREEN_WIDTH/MAX_WIDTH_UNIT*���λ��
//#define MAX_HEIGHT_UNIT 562 //���߶ȵ�λ ʵ��λ��= SCREEN_HEIGHT/MAX_HEIGHT_UNIT*���λ��


//�궨��ĺ���
#define SCHEDULE(fPeriodSecond,DoWhat) if (fTime != 0){static float fLastTime = 0;	if (fTime - fLastTime < fPeriodSecond){	DoWhat; return true;}	else fLastTime = fTime;}
#define SCHEDULE2(fPeriodSecond,DoWhat) if (fTime != 0){static float fLastTime2 = 0;	if (fTime - fLastTime2 < fPeriodSecond){	DoWhat; return true;}	else fLastTime2 = fTime;}







#endif