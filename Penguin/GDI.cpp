#include "stdafx.h"
#include "GDI.h"

#ifndef _SERVER_


#pragma comment(lib,"Msimg32.lib")


#ifndef _D2DRender_

CGDI::CGDI(){
	m_Hdc=NULL;
	m_hRenderBuffer=NULL;
}

CGDI::~CGDI(){
	if (m_Hdc) DeleteObject(m_Hdc);
	if (m_hRenderBuffer) DeleteObject(m_hRenderBuffer);
}


bool CGDI::DrawLine(HDC hdc, int _dot1x, int _dot1y, int _dot2x, int _dot2y,
	int nWidth, DWORD dwColor){

	HPEN hPen;
	hPen = CreatePen(PS_SOLID, nWidth, dwColor);
	SelectObject(hdc, hPen);
	MoveToEx(hdc, _dot1x, _dot1y, 0);
	LineTo(hdc, _dot2x, _dot2y);
	DeleteObject(hPen);
	return true;
}


bool CGDI::DrawLineEx(HDC hdc, int _dot1x, int _dot1y, int _dot2x, int _dot2y,
	ePenStyle nPenStyle, int nWidth, DWORD dwColor){

	HPEN hPen;
	hPen = CreatePen(nPenStyle, nWidth, dwColor);
	SelectObject(hdc, hPen);
	MoveToEx(hdc, _dot1x, _dot1y, 0);
	LineTo(hdc, _dot2x, _dot2y);
	DeleteObject(hPen);
	return true;
}

bool CGDI::DrawRectangle(HDC hdc, int _dot1x, int _dot1y, int _dot2x, int _dot2y,
	int nWidth, DWORD dwColor){

	HPEN hPen;
	hPen = CreatePen(PS_SOLID, nWidth, dwColor);
	SelectObject(hdc, hPen);
	SelectObject(hdc, GetStockObject(NULL_BRUSH));
	Rectangle(hdc, _dot1x, _dot1y, _dot2x, _dot2y);
	DeleteObject(hPen);
	return true;
}

bool CGDI::DrawRectangleEx(HDC hdc, int _dot1x, int _dot1y, int _dot2x, int _dot2y,
	ePenStyle nPenStyle, int nWidth, DWORD dwColor){

	HPEN hPen;
	hPen = CreatePen(nPenStyle, nWidth, dwColor);
	SelectObject(hdc, hPen);
	Rectangle(hdc, _dot1x, _dot1y, _dot2x, _dot2y);
	DeleteObject(hPen);
	return true;
}

bool CGDI::DrawSolidRectangle(HDC hdc, int _dot1x, int _dot1y, int _dot2x, int _dot2y,
	DWORD dwColor){

	HBRUSH hBrush;
	hBrush = CreateSolidBrush(dwColor);
	SelectObject(hdc, hBrush);
	Rectangle(hdc, _dot1x, _dot1y, _dot2x, _dot2y);
	DeleteObject(hBrush);
	return true;
}

bool CGDI::DrawSolidRectangle(HDC hdc, Line _line,
	DWORD dwColor){
	return DrawSolidRectangle(hdc, _line.nP1.nx, _line.nP1.ny, _line.nP2.nx, _line.nP2.ny);
}

bool CGDI::DrawSolidRectangleEx(HDC hdc, int _dot1x, int _dot1y, int _dot2x, int _dot2y,
	DWORD dwColor, int nBorderWidth, DWORD dwBorderColor){
	DrawRectangle(hdc, _dot1x, _dot1y, _dot2x, _dot2y, nBorderWidth, dwBorderColor);
	DrawSolidRectangle(hdc, _dot1x, _dot1y, _dot2x, _dot2y, dwColor);
	return true;
}

bool CGDI::DrawTextB(HDC hdc, int _dot1x, int _dot1y, int _dot2x, int _dot2y,
	LPCTSTR lpString, bool bCenter){
	RECT rt;
	UINT uFormat = DT_SINGLELINE;
	rt.left = _dot1x;
	rt.top = _dot1y;
	rt.right = _dot2x;
	rt.bottom = _dot2y;
	if (bCenter)
		uFormat |= DT_CENTER;
	SetBkMode(hdc, TRANSPARENT);
	DrawText(hdc, lpString, -1, &rt, uFormat);

	return true;
}

bool CGDI::DrawTextB(HDC hdc, Point _p1, Point _p2,
	LPCTSTR lpString, bool bCenter){
	return DrawTextB(hdc, _p1.nx, _p1.ny, _p2.nx, _p2.ny, lpString, bCenter);
}


HBITMAP CGDI::LoadBmpFile(LPCTSTR pFileName){
	//加在bmp文件
	return (HBITMAP)LoadImage(NULL, pFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

bool CGDI::DrawBmp(HDC hdc, LPCTSTR pFileName, int _x, int _y, int _width, int _height,
	int nSrcX, int nSrcY){

	HDC Hdc;
	HBITMAP hBitmap;
	Hdc = CreateCompatibleDC(hdc);
	hBitmap = LoadBmpFile(pFileName);
	SelectObject(Hdc, hBitmap);
	BitBlt(hdc, _x, _y, _width, _height, Hdc, nSrcX, nSrcY, SRCCOPY);
	DeleteObject(hBitmap);
	DeleteObject(Hdc);
	return true;
}

bool CGDI::DrawTransparentBmp(HDC hdc, LPCTSTR pFileName, int _x, int _y, int _width, int _height,
	int nSrcX, int nSrcY, DWORD bkColor){

	HDC Hdc;
	HBITMAP hBitmap;
	Hdc = CreateCompatibleDC(hdc);
	hBitmap = LoadBmpFile(pFileName);
	SelectObject(Hdc, hBitmap);
	//BitBlt(hdc,_x,_y,_width,_height,Hdc,nSrcX,nSrcY,SRCCOPY);
	TransparentBlt(hdc, _x, _y, _width, _height, Hdc, nSrcX, nSrcY, _width, _height, bkColor);
	DeleteObject(hBitmap);
	DeleteObject(Hdc);
	return true;
}

bool CGDI::DrawTransparentBmp(HDC hdc, HBITMAP hBitmap, int _x, int _y, int _width, int _height,
	int nSrcX, int nSrcY, DWORD bkColor){

	HDC Hdc;
	Hdc = CreateCompatibleDC(hdc);
	SelectObject(Hdc, hBitmap);
	//BitBlt(hdc,_x,_y,_width,_height,Hdc,nSrcX,nSrcY,SRCCOPY);
	TransparentBlt(hdc, _x, _y, _width, _height, Hdc, nSrcX, nSrcY, _width, _height, bkColor);
	//DeleteObject(hBitmap);
	DeleteObject(Hdc);
	return true;
}

bool CGDI::CreateRenderBuffer(HDC hdc, int _width, int _height){
	m_pResolution = Point(_width, _height);
	if (m_Hdc) DeleteObject(m_Hdc);
	if (m_hRenderBuffer) DeleteObject(m_hRenderBuffer);
	m_Hdc = CreateCompatibleDC(NULL);
	m_hRenderBuffer = CreateCompatibleBitmap(hdc, _width, _height);
	SelectObject(m_Hdc, m_hRenderBuffer);
	return true;
}

HDC CGDI::GetTempHdc(){
	return m_Hdc;
}

bool	CGDI::NotifyChange(HDC hdc){
	return (BitBlt(hdc, 0, 0, m_pResolution.nx, m_pResolution.ny, m_Hdc, 0, 0, SRCCOPY)!=0);
}

#else

#endif

#endif