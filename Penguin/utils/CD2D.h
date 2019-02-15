#pragma once

#include <Windows.h>
#include <D2D1.h>// header for Direct2D
#include <d2d1helper.h>  
#include <Dwrite.h>


#include <atlstr.h>
#include <wincodec.h>  
#include "Arith.h"

using namespace std;

#ifndef SAFE_RELEASE
	#define SAFE_RELEASE(P) if(P){P->Release() ; P = NULL ;}
#endif

#define Fatal(msg) FatalAppExit(0,msg);

class CD2DImage;


extern DWORD D2DRGB(BYTE r, BYTE g, BYTE b);

class CD2D{
public:
	CD2D();
	~CD2D();

public:
	//初始化
	BOOL CreateD2DResource(HWND hWnd, bool IsVerticalSync = true);
	//开始绘画
	void	BeginDraw();
	//结束绘画
	void	EndDraw();
	//清屏
	BOOL ClearScreen();
	BOOL ClearScreen(FLOAT r, FLOAT g, FLOAT b, FLOAT a = 1.0F);
	BOOL ClearScreen(D2D1::ColorF::Enum clearColor);

	//画文本
	BOOL DrawTextB(LPCTSTR sFontName, FLOAT fFontSize,
		FLOAT left, FLOAT top, FLOAT right, FLOAT bottom, CString sText, bool AlienToRight = false, bool bYellow = false, FLOAT _alpha=1.0F);
	BOOL DrawTextC(LPCTSTR sFontName, FLOAT fFontSize,
		FLOAT left, FLOAT top, FLOAT right, FLOAT bottom, CString sText, DWORD rgb = 0, FLOAT _Alpha = 1.0F, bool AlienToRight = false);

	//画矩形
	BOOL DrawGeometry(ID2D1Bitmap* _bitmap);

	BOOL DrawRectangle(FLOAT left, FLOAT top, FLOAT right, FLOAT bottom,FLOAT _width=1.0F);

	//画图像
	BOOL DrawBitmap(CD2DImage Image, FLOAT _x, FLOAT _y, FLOAT _width, FLOAT _height, 
		FLOAT alpha=1.0F, int nSrcX = 0, int nSrcY = 0, int nSrcWidth = 0, int nSrcHeight = 0);

	BOOL DrawRotateBitmap(CD2DImage Image, FLOAT _x, FLOAT _y, FLOAT _width, FLOAT _height,
		FLOAT alpha = 1.0F, int nSrcX = 0, int nSrcY = 0, int nSrcWidth = 0, int nSrcHeight = 0,float angel = 0);
	
	//清理
	void Cleanup(void);

	static ID2D1HwndRenderTarget* GetRenderTarget();
protected:

private:
	ID2D1Factory*				m_pD2DFactory;              // Direct2D factory
	static ID2D1HwndRenderTarget*	m_pRenderTarget;   // Render target
	ID2D1SolidColorBrush*		m_pBlackBrush;      // A black brush, reflect the line color
	IDWriteFactory*				m_pDWriteFactory;     //Dwrite
	ID2D1SolidColorBrush*		m_pWhiteBrush;
	ID2D1SolidColorBrush*		m_pBlueBrush;
	ID2D1SolidColorBrush*		m_pYellowBrush;

	                              // Render area
	HWND m_hWnd;                             // Window handle
};

