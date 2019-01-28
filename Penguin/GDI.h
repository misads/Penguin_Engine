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

	//��һ��ֱ��
	bool DrawLine(HDC Hdc, int _dot1x, int _dot1y, int _dot2x, int _dot2y,
		int nWidth = 1, DWORD dwColor = 0);

	bool DrawLineEx(HDC hdc, int _dot1x, int _dot1y, int _dot2x, int _dot2y,
		ePenStyle nPenStyle, int nWidth = 1, DWORD dwColor = 0);

	bool DrawRectangle(HDC hdc, int _dot1x, int _dot1y, int _dot2x, int _dot2y,
		int nWidth = 1, DWORD dwColor = 0);

	bool DrawRectangleEx(HDC hdc, int _dot1x, int _dot1y, int _dot2x, int _dot2y,
		ePenStyle nPenStyle, int nWidth = 1, DWORD dwColor = 0);
	//��ʵ�ľ���
	bool DrawSolidRectangle(HDC hdc, int _dot1x, int _dot1y, int _dot2x, int _dot2y,
		DWORD dwColor = 0);

	bool DrawSolidRectangle(HDC hdc, Line _line,
		DWORD dwColor = 0);
	bool DrawSolidRectangleEx(HDC hdc, int _dot1x, int _dot1y, int _dot2x, int _dot2y,
		DWORD dwColor, int nBorderWidth, DWORD dwBorderColor);
	//�����ı�
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

	//����һ��ͼƬ�ڴ滺��,
	bool CreateRenderBuffer(HDC hdc, int _width, int _height);
	//��ȡ��ʱHDC,��������ʱHDC�ϻ�ͼ
	HDC GetTempHdc();
	//������Ļ�����ڴ滺�滭����Ļ��
	bool	NotifyChange(HDC hdc);

	HBITMAP		LoadBmpFile(LPCTSTR pFileName);
protected:
	
	
	HDC				m_Hdc;						//��ʱHDC
	HBITMAP		m_hRenderBuffer;			//��ʱͼƬ

	Point			m_pResolution;				//�ֱ���
};


#else




#endif




#endif


#endif