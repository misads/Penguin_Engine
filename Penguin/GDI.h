#ifndef _SERVER_

#include<windows.h>
#include "CommonHead.h"
#include "Arith.h"

#ifndef _H_RENDER_H
#define _H_RENDER_H
#pragma once

#ifndef _D2DRender_

enum ePenStyle{ SOLID, DASH, DOT, DASHDOT, DASHDOTDOT };



class CGDI{
public:
	CGDI(void);
	~CGDI(void);

	//画一条直线
	bool DrawLine(HDC Hdc, int _dot1x, int _dot1y, int _dot2x, int _dot2y,
		int nWidth = 1, DWORD dwColor = 0);

	bool DrawLineEx(HDC hdc, int _dot1x, int _dot1y, int _dot2x, int _dot2y,
		ePenStyle nPenStyle, int nWidth = 1, DWORD dwColor = 0);

	bool DrawRectangle(HDC hdc, int _dot1x, int _dot1y, int _dot2x, int _dot2y,
		int nWidth = 1, DWORD dwColor = 0);

	bool DrawRectangleEx(HDC hdc, int _dot1x, int _dot1y, int _dot2x, int _dot2y,
		ePenStyle nPenStyle, int nWidth = 1, DWORD dwColor = 0);
	//画实心矩形
	bool DrawSolidRectangle(HDC hdc, int _dot1x, int _dot1y, int _dot2x, int _dot2y,
		DWORD dwColor = 0);

	bool DrawSolidRectangle(HDC hdc, Line _line,
		DWORD dwColor = 0);
	bool DrawSolidRectangleEx(HDC hdc, int _dot1x, int _dot1y, int _dot2x, int _dot2y,
		DWORD dwColor, int nBorderWidth, DWORD dwBorderColor);
	//绘制文本
	bool DrawTextB(HDC hdc, int _dot1x, int _dot1y, int _dot2x, int _dot2y,
		LPCTSTR lpString, bool bCenter = false);
	
	bool DrawTextB(HDC hdc, Point _p1, Point _p2,
		LPCTSTR lpString, bool bCenter = false);

	bool DrawBmp(HDC hdc, LPCTSTR pFileName, int _x, int _y, int _width, int _height,
		int nSrcX = 0, int nSrcY = 0);

	bool DrawTransparentBmp(HDC hdc, LPCTSTR pFileName, int _x, int _y, int _width, int _height,
		int nSrcX = 0, int nSrcY = 0, DWORD bkColor = RGB(255, 255, 255));
	
	bool DrawTransparentBmp(HDC hdc, HBITMAP hBitmap, int _x, int _y, int _width, int _height,
		int nSrcX = 0, int nSrcY = 0, DWORD bkColor = RGB(255, 255, 255));

	//创建一个图片内存缓存,
	bool CreateRenderBuffer(HDC hdc, int _width, int _height);
	//获取临时HDC,可以在临时HDC上画图
	HDC GetTempHdc();
	//更新屏幕，把内存缓存画到屏幕上
	bool	NotifyChange(HDC hdc);

	HBITMAP		LoadBmpFile(LPCTSTR pFileName);
protected:
	
	
	HDC				m_Hdc;						//临时HDC
	HBITMAP		m_hRenderBuffer;			//临时图片

	Point			m_pResolution;				//分辨率
};


#else




#endif




#endif


#endif